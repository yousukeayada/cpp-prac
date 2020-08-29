#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define MESSAGE "Hello World!"

using namespace std;

int main(void)
{
    // ソケット作成
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket");
        return 1;
    }
    cout << "sock: " << sock << endl;

    // struct sockaddr_un 作成
    struct sockaddr_un sa = {0};
    sa.sun_family = AF_UNIX;
    strcpy(sa.sun_path, "./unix-domain-socket");

    // 接続
    int con = connect(sock, (struct sockaddr*) &sa, sizeof(struct sockaddr_un));
    if (con == -1)
    {
        perror("connect");
        // goto bail;
    }
    cout << "connect: " << con << endl;

    // 送信
    if (write(sock, MESSAGE, strlen(MESSAGE)) == -1)
    {
        perror("write");
        // goto bail;
    }

    // 受信
    char buffer[4096];
    int recv_size = read(sock, buffer, sizeof(buffer) - 1);
    if (recv_size == -1)
    {
        perror("read");
        close(sock);
        goto bail;
    }
    // 受信内容を表示
    buffer[recv_size] = '\0';
    cout << "message: " << buffer << endl;


    // クローズ
    close(sock);
    return 0;
 
bail:
    // エラーが発生した場合の処理
    close(sock);
    return 1;
}