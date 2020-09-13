#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

#define print(var) cout << var << endl;

int main() {
    string s = "hello";
    const char* c = s.c_str();
    cout << strlen((char*)c) << endl;

    const string str = "hoge";
    print(str)

    const string METHOD = "GET";
    const string PATH = "/";
    const string HTTPVER = "HTTP/1.1";
    const string REQUEST = METHOD + " " + PATH + " " + HTTPVER + "\n";
    print(REQUEST.c_str())

    string host;
    cout << "input host: "; cin >> host;
    const char* url = ("http://" + host).c_str();
    string url_host(url, 7, strlen(url)-1);
    const string HEADER = "Host: " + url_host + "\n"
                        + "Accept: */*\n";
    const string MESSAGE = REQUEST + HEADER;
    print(MESSAGE)

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // struct hostent *hostent1;
    // hostent1 = gethostbyname("google.com");
    // struct in_addr inaddr1;
    // inaddr1.s_un.s_addr = **(unsigned int **)(hostent1->h_addr_list);
    print(server.sin_addr.s_addr)

    return 0;
}