#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>

using namespace std;

#define HOST "127.0.0.1"
#define PORT 14235

int main() {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    // ソケット生成
    int sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0) {
        cout << "socket error: " << strerror(errno) << endl;
        exit(1);
    }
    cout << "created socket" << endl;

    // アドレス生成
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(HOST);

    // ソケット接続要求
    connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    cout << "connected to " << HOST << endl;

    while(true) {
        // データ送信
        char s_buf[256];
        cout << "input: "; cin >> s_buf;
        if(strcmp(s_buf, "quit") == 0) {
            break;
        }
        send(sockfd, s_buf, 256, 0);
        cout << hostname << ": " << s_buf << endl;

        // データ受信
        char r_buf[256];
        recv(sockfd, r_buf, 256, 0);
        cout << HOST << ": " << r_buf << endl;
    }

    // ソケットクローズ
    close(sockfd);

    return 0;
}