/*---------------------------------------------------------------------------------------------------------------------------------------------------
                                                           Projekt na przedmiot programowanie sieciowe 
                                                           AGH III rok, Elektronika i Telekomunikacja
                                                           Krzysztof Szczepański
							   Prowadzący: Karol Salwik
							   Temat: Usługa komunikatora tekstowego z przechowywaniem kont i historii na serwerze
							   Program serwer
---------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <syslog.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include "common.h"

#define MAX_CLIENTS 100
#define USERS_TXT_PATH "/home/chris/Desktop/projekt PS/users.txt" //proszę podać tu dokładną ścieżkę do users.txt
#define HISTORIA_TXT_PATH "/home/chris/Desktop/projekt PS/historia.txt" //proszę podać tu dokładną ścieżkę do historia.txt

static _Atomic unsigned int cli_count = 0;
static int uid = 10;
int DEBUG_MODE = 1;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[32];
} client_t;

client_t *clients[MAX_CLIENTS];

void log_event(const char *msg) {
    if (DEBUG_MODE) {
        printf("[LOG] %s\n", msg);
    } else {
        syslog(LOG_INFO, "%s", msg);
    }

    pthread_mutex_lock(&file_mutex);
    FILE *fp = fopen(HISTORIA_TXT_PATH, "a"); 
    if (fp) {
        time_t now = time(NULL);
        char *t = ctime(&now);
        t[strlen(t)-1] = '\0';
        fprintf(fp, "[%s] %s\n", t, msg);
        fclose(fp);
    }
    pthread_mutex_unlock(&file_mutex);
}

int check_credentials(char *login, char *password) {
    FILE *fp = fopen( USERS_TXT_PATH , "r");
    
    if (!fp) {
        if(DEBUG_MODE) printf("BŁĄD: Nie znaleziono pliku users.txt\n");
        return 0; 
    }

    char line[100];
    int auth = 0;
    while(fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0; 
        char *f_login = strtok(line, ":");
        char *f_pass = strtok(NULL, ":");

        if(f_login && f_pass) {
            if(strcmp(login, f_login) == 0 && strcmp(password, f_pass) == 0) {
                auth = 1;
                break;
            }
        }
    }
    fclose(fp);
    return auth;
}

void skeleton_daemon() {
    pid_t pid;
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    if (setsid() < 0) exit(EXIT_FAILURE);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);
    umask(0);
    chdir("/");
    for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close(x);
    }
    openlog("ChatServer", LOG_PID, LOG_DAEMON);
}

void *multicast_beacon(void *arg) {
    int sock;
    struct sockaddr_in addr;
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MC_GROUP);
    addr.sin_port = htons(MC_PORT);

    while(1) {
        char *beacon = "CHAT_SERVER_HERE";
        sendto(sock, beacon, strlen(beacon), 0, (struct sockaddr*)&addr, sizeof(addr));
        sleep(5); 
    }
    return NULL;
}

void broadcast_tlv(tlv_packet_t packet, int sender_uid) {
    pthread_mutex_lock(&clients_mutex);
    for(int i=0; i<MAX_CLIENTS; ++i) {
        if(clients[i] && clients[i]->uid != sender_uid) {
            send(clients[i]->sockfd, &packet, sizeof(packet), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    client_t *cli = (client_t *)arg;
    tlv_packet_t packet;
    char log_buf[2048];
    int is_authenticated = 0;

    while(recv(cli->sockfd, &packet, sizeof(packet), 0) > 0) {
        if (packet.type == MSG_LOGIN) {
            char *login = strtok(packet.value, ":");
            char *pass = strtok(NULL, ":");

            if (login && pass && check_credentials(login, pass)) {
                is_authenticated = 1;
                strcpy(cli->name, login);
                
                sprintf(log_buf, "Użytkownik %s zalogował się.", cli->name);
                log_event(log_buf);
                
                tlv_packet_t ack;
                ack.type = MSG_ACK;
                strcpy(ack.value, "Zalogowano pomyślnie!");
                send(cli->sockfd, &ack, sizeof(ack), 0);
            } else {
                log_event("Nieudana próba logowania.");
                
                tlv_packet_t fail;
                fail.type = MSG_FAIL;
                strcpy(fail.value, "Błędny login lub hasło.");
                send(cli->sockfd, &fail, sizeof(fail), 0);
                break; 
            }

        } else if (packet.type == MSG_TEXT) {
            if (!is_authenticated) break; 

            sprintf(log_buf, "%s: %s", cli->name, packet.value);
            log_event(log_buf);
            
            tlv_packet_t forward;
            forward.type = MSG_TEXT;
            strcpy(forward.value, log_buf);
            broadcast_tlv(forward, cli->uid);
            
        } else if (packet.type == MSG_EXIT) {
            break;
        }
    }

    close(cli->sockfd);
    
    pthread_mutex_lock(&clients_mutex);
    for(int i=0; i<MAX_CLIENTS; ++i){
        if(clients[i] == cli) {
            clients[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    if (is_authenticated) {
        sprintf(log_buf, "Użytkownik %s rozłączył się.", cli->name);
        log_event(log_buf);
    }
    free(cli);
    return NULL;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        DEBUG_MODE = 0;
        printf("Uruchamiam w trybie DEMONA (brak wyjścia w konsoli, logi w syslog).\n");
        skeleton_daemon();
        syslog(LOG_NOTICE, "Serwer Czat wystartował.");
    } else {
        printf("Uruchamiam w trybie DEBUG (widoczne logi).\n");
        printf("Aby uruchomić jako demon, wpisz: ./server -d\n");
    }

    pthread_t mc_thread;
    pthread_create(&mc_thread, NULL, multicast_beacon, NULL);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }
    listen(listenfd, 10);

    if (DEBUG_MODE) printf("Serwer nasłuchuje na porcie %d...\n", SERVER_PORT);

    while(1) {
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->sockfd = connfd;
        cli->uid = uid++;
        
        pthread_mutex_lock(&clients_mutex);
        for(int i=0; i<MAX_CLIENTS; ++i){
            if(!clients[i]){
                clients[i] = cli;
                break;
            }
        }
        pthread_mutex_unlock(&clients_mutex);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, (void*)cli);
    }
    
    if (!DEBUG_MODE) closelog();
    return 0;
}





