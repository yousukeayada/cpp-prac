- ソケットプログラム

- https://www.khstasaba.com/?p=401
  - int socket(int protocolFamily, int type, int protocol)
    - PF_INET＋SOCK_STREAM＋IPPROTO_TCP・・TCP/IPv4
    - PF_INET＋SOCK_DGRAM＋IPPROTO_UDP・・UDP/IPv4
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