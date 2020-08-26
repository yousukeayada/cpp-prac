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
    // ソケット生成
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    // データ送信
    char s_buf[256];
    cout << "input: "; cin >> s_buf;
    send(sockfd, s_buf, 256, 0);
    cout << "sent: " << s_buf << endl;

    // データ受信
    char r_buf[256];
    recv(sockfd, r_buf, 256, 0);
    cout << "received: " << r_buf << endl;

    // ソケットクローズ
    close(sockfd);

    return 0;
}