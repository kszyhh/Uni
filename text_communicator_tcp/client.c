/*---------------------------------------------------------------------------------------------------------------------------------------------------
                                                           Projekt na przedmiot programowanie sieciowe 
                                                           AGH III rok, Elektronika i Telekomunikacja
                                                           Krzysztof Szczepański
               						   Prowadzący: Karol Salwik
							   Temat: Usługa komunikatora tekstowego z przechowywaniem kont i historii na serwerze
							   Program klient
---------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "common.h"

int sockfd = 0;

void find_server_ip(char *found_ip) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    u_int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(MC_PORT);
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MC_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    printf("Szukam serwera w sieci (Multicast)...\n");
    char buf[100];
    struct sockaddr_in src_addr;
    socklen_t addrlen = sizeof(src_addr);
    
    recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&src_addr, &addrlen);
    
    strcpy(found_ip, inet_ntoa(src_addr.sin_addr));
    printf("Znaleziono serwer: %s\n", found_ip);
    close(sock);
}

void resolve_dns(const char *hostname, char *ip_str) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; 
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        printf("Błąd DNS. Używam domyślnego IP 127.0.0.1\n");
        strcpy(ip_str, "127.0.0.1");
        return;
    }
    
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    inet_ntop(AF_INET, &(ipv4->sin_addr), ip_str, INET_ADDRSTRLEN);
    freeaddrinfo(res);
}

void *recv_handler(void *arg) {
    tlv_packet_t packet;
    while (1) {
        int ret = recv(sockfd, &packet, sizeof(packet), 0);
        if (ret > 0) {
            printf("\r%s\n> ", packet.value);
            fflush(stdout);
        } else {
            printf("\nRozłączono z serwerem.\n");
            exit(0);
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    char ip[INET_ADDRSTRLEN];
    
    printf("1. Wykryj serwer automatycznie (Multicast)\n");
    printf("2. Podaj adres/nazwę ręcznie\nWybor: ");
    int choice;
    scanf("%d", &choice);
    getchar(); 

    if (choice == 1) {
        find_server_ip(ip);
    } else {
        char host[100];
        printf("Podaj nazwę hosta lub IP: ");
        fgets(host, 100, stdin);
        host[strcspn(host, "\n")] = 0; 
        resolve_dns(host, ip);
    }

    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(SERVER_PORT);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    char login[50], pass[50];
    printf("Podaj login: ");
    fgets(login, 50, stdin);
    login[strcspn(login, "\n")] = 0;

    printf("Podaj hasło: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = 0;

    tlv_packet_t msg;
    msg.type = MSG_LOGIN;
    sprintf(msg.value, "%s:%s", login, pass); 
    send(sockfd, &msg, sizeof(msg), 0);

    tlv_packet_t resp;
    recv(sockfd, &resp, sizeof(resp), 0);
    
    if (resp.type == MSG_FAIL) {
        printf("BŁĄD: %s\n", resp.value);
        close(sockfd);
        return 0;
    } else {
        printf("SUKCES: %s\n", resp.value);
    }

    pthread_t tid;
    pthread_create(&tid, NULL, recv_handler, NULL);

    while(1) {
        printf("> ");
        fgets(msg.value, 1000, stdin);
        msg.value[strcspn(msg.value, "\n")] = 0;
        
        if (strcmp(msg.value, "exit") == 0) {
            msg.type = MSG_EXIT;
            send(sockfd, &msg, sizeof(msg), 0);
            break;
        } else {
            msg.type = MSG_TEXT;
            msg.length = strlen(msg.value);
            send(sockfd, &msg, sizeof(msg), 0);
        }
    }
    close(sockfd);
    return 0;
}
