#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

using namespace std;

int main(void)
{
    // サーバーソケット作成
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
    cout << "AF_UNIX: " << AF_UNIX << endl;

    // 既に同一ファイルが存在していたら削除
    remove(sa.sun_path);

    // バインド
    int b = bind(sock, (struct sockaddr*) &sa, sizeof(struct sockaddr_un));
    if (b == -1)
    {
        perror("bind");
        // goto bail;
    }
    cout << "bind: " << b << endl;

    // リッスン
    int l = listen(sock, 128);
    if (l == -1)
    {
        perror("listen");
        goto bail;
    }
    cout << "listen: " << l << endl;

    while (1)
    {
        // クライアントの接続を待つ
        int fd = accept(sock, NULL, NULL);
        if (fd == -1)
        {
            perror("accept");
            goto bail;
        }
        cout << "accept: " << fd << endl;

        // 受信
        char buffer[4096];
        int recv_size = read(fd, buffer, sizeof(buffer) - 1);
        if (recv_size == -1)
        {
            perror("read");
            close(fd);
            goto bail;
        }
        cout << "recv_size: " << recv_size << endl;

        // 受信内容を表示
        buffer[recv_size] = '\0';
        cout << "message: " << buffer << endl;

        // 送信
        if (write(fd, buffer, recv_size) == -1)
        {
            perror("write");
            // goto bail;
        }

        // ソケットのクローズ
        if (close(fd) == -1)
        {
            perror("close");
            goto bail;
        }
    }

bail:
    // エラーが発生した場合の処理
    close(sock);
    return 1;
}