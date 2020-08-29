#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    if(chmod("test.cc", 0777) < 0) { // umask は無関係
        perror("chmod failed");
        return 1;
    }
    // if(chown("sample.txt", 123, 456) < 0) { // uid, gid
    //     perror("chown failed");
    //     return 1;
    // }
    return 0;
}