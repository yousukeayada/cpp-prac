#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include <netdb.h>
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
    struct hostent *host;
    host = gethostbyname("localhost");
	if (host == NULL) {
		return 1;
	}
	addr.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
    // addr.sin_addr.s_addr = inet_addr(HOST);

    // ソケット接続要求
    connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    cout << "connected to " << inet_ntoa(addr.sin_addr) << endl;

    while(true) {
        // データ送信
        string input;
        cout << "input: "; cin >> input;
        const char* s_buf = input.c_str();
        if(strcmp(s_buf, "quit") == 0) {
            break;
        }

        send(sockfd, s_buf, strlen((char*)s_buf), 0);
        cout << hostname << ": " << s_buf << endl;

        // データ受信
        char r_buf[BUFSIZE];
        recv(sockfd, r_buf, BUFSIZE, 0);
        cout << HOST << ": " << r_buf << endl;
    }

    // ソケットクローズ
    close(sockfd);

    return 0;
}