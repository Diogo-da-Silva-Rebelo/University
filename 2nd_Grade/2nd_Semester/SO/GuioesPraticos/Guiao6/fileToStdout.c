#include "namedPipes.h"

int main(int argc, const char* argv[]) {
    int fd_source = open("/tmp/fifo", O_RDONLY);
    int bytes_read = 0;
    char *buf = malloc(sizeof(char) * 1024);

    if (fd_source == -1) {
        perror("open");
        printf("open error: %d texto: %s\n", errno, strerror(errno));
        return -1;
    }

    while ((bytes_read = read(fd_source, buf, 1024)) > 0) {
        write(1, buf, bytes_read);
    }

    close(fd_source);

    return 0;
}
