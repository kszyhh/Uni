import ftplib
import os

os.system('cls' if os.name == 'nt' else 'clear')

ftp_host = "test.rebex.net"  # hostname
ftp_user = "demo"  # username
ftp_password = "password"  # password
ftp_port = 21  # port

try:
    ftp = ftplib.FTP()
    ftp.connect(ftp_host, ftp_port)
    ftp.login(passwd=ftp_password, user=ftp_user)
    print(f">Content of the {ftp_host} server:")
    ftp.dir() #ls
    file_list = ftp.nlst() 

    while True:
        ans = input(">Insert name of the file you'd like to download: ")

        if ans not in file_list:
            print(">There is no such a file.")
            continue
        break
    print(f">Downloading {ans}...")
    with open(ans, "wb") as f:
        ftp.retrbinary(f"RETR {ans}", f.write) #retrive and save as binary
    print(f">Done. {ans} downloaded successfully.")

    ftp.quit()
except ftplib.all_errors:
    print(">An error has occured.")
