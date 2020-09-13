#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>

using namespace std;

#define HOST "127.0.0.1"
#define PORT 14235

#define BUFSIZE 65535

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

    // ソケット登録
    if(bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        cout << "bind error: " << strerror(errno) << endl;
        exit(1);
    }
    cout << "bound socket" << endl;

    // 受信待ち
    if(listen(sockfd, SOMAXCONN) < 0) {
        cout << "listen error: " << strerror(errno) << endl;
        close(sockfd);
        exit(1);
    }
    cout << "listening at " << HOST << ":" << PORT << "..." << endl;

    // 接続待ち
    struct sockaddr_in get_addr; //接続相手のソケットアドレス
    socklen_t len = sizeof(struct sockaddr_in);
    int connect = accept(sockfd, (struct sockaddr *)&get_addr, &len);
    if(connect < 0) {
        cout << "accept error: " << strerror(errno) << endl;
        exit(1);
    }
    cout << "connected from " << inet_ntoa(get_addr.sin_addr) << endl;

    while(true) {
        // データ受信
        char r_buf[BUFSIZE];
        recv(connect, r_buf, BUFSIZE, 0);
        cout << inet_ntoa(get_addr.sin_addr) << ": " << r_buf << endl;

        // データ送信
        send(connect, r_buf, BUFSIZE, 0);
        cout << hostname << ": " << r_buf << endl;
    }

    // ソケットクローズ
    close(connect);
    close(sockfd);

    return 0;
}