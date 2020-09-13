#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string>

using namespace std;

#define PORT 80

#define BUFSIZE 65535

void get(const char* url);

int main() {
    
    string host;
    cout << "input host: "; cin >> host;
    const char* url = ("http://" + host).c_str();
    get(url);

    return 0;
}

void get(const char* url) {
    // HTTP メッセージ作成
    const string METHOD = "GET";
    const string PATH = "/";
    const string HTTPVER = "HTTP/1.0";
    const string REQUEST = METHOD + " " + PATH + " " + HTTPVER + "\r\n\r\n";
    string host(url, 7, strlen(url)-1);
    const string HEADER = "Host: " + host + "\r\n"
                        + "User-Agent: curl/7.64.1\r\n"
                        + "Accept: */*\r\n"
                        + "Connection: Keep-Alive\r\n"
                        ;
    const string MESSAGE = REQUEST + HEADER;


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
    struct hostent *ent;
    ent = gethostbyname(host.c_str());
    if (ent == NULL) {
        cout << "cannot resolve hostname" << endl;
		exit(1);
	}
	addr.sin_addr.s_addr = *(unsigned int *)ent->h_addr_list[0];
    // addr.sin_addr.s_addr = inet_addr(host.c_str());

    // ソケット接続要求
    int con = connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if (con == -1) {
        perror("connect");
        close(sockfd);
        exit(1);
    }
    cout << "connected to " << host << "(" << inet_ntoa(addr.sin_addr) << ") port " << PORT << endl;

    // データ送信
    const char* msg = MESSAGE.c_str();
    int s = send(sockfd, msg, strlen(msg), 0);
    if(s < 0) {
        perror("send");
        close(sockfd);
        exit(1);
    }
    cout << "sent below message" << endl;
    cout << "==================" << endl;
    cout << msg << endl;
    cout << "==================" << endl;

    // データ受信
    char r_buf[BUFSIZE];
    int recv_size = recv(sockfd, r_buf, BUFSIZE, 0);
    if (recv_size == -1) {
        perror("recv");
        close(sockfd);
        exit(1);
    }
    cout << "response" << endl;
    cout << "==================" << endl;
    cout << r_buf << endl;
    cout << "==================" << endl;

    // int n = s;
    // char buf[32];
    // while (n > 0) {
    //     memset(buf, 0, sizeof(buf));
	//     n = read(sockfd, buf, sizeof(buf));
	//     if (n < 0) {
	// 	    perror("read");
	// 	    exit(1);
	//     }

	//     /* 受信結果を標準出力へ表示(ファイルディスクリプタ1は標準出力) */
	//     write(1, buf, n);
    // }
    

    // ソケットクローズ
    close(sockfd);
}
