## Socket API を使ったプログラム

- https://www.khstasaba.com/?p=401
  - int socket(int protocolFamily, int type, int protocol)
    - PF_INET + SOCK_STREAM + IPPROTO_TCP・・TCP/IPv4
    - PF_INET + SOCK_DGRAM + IPPROTO_UDP・・UDP/IPv4
    - AF_UNIX + SOCK_STREAM/SOCK_DGRAM・・UNIX ドメインソケット
  - ```bash
    struct sockaddr_in
    {
    　unsigned short sin_family;
    　unsigned short sin_port;
    　struct in_addr sin_addr;
    　char sin_zero[8];
    }
    ```
- TCP：send, recv
- UDP：sendto, recvfrom
- UNIX ドメインソケット：write, read

- http://www.tohoho-web.com/ex/http.htm
  - HTTP メッセージの中身
- https://www.geekpage.jp/programming/linux-network/http-client.php
  - `gethostbyname()` で名前解決する
  - `GET / HTTP/1.0\r\n\r\n`
    - 1.1 だとなぜかダメ
    - \r\n も2個ないとダメ
- https://www.geekpage.jp/programming/linux-network/gethostbyname.php
  - `gethostbyname()` の使い方
  