#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define FILENAME "lab2_task2.txt"

int main() {
    char *filename = FILENAME;
    int fd = open(filename, O_RDWR);

    char buf[BUFFER_SIZE];
    int read_bytes = read(fd, buf, BUFFER_SIZE);
    if(read_bytes < 0) {
        printf("Error while reading data from file.\nCreate file named \"lab2_task2.txt\" and try again\n");
    } else {
        printf("Files original contents:\n%s\n", buf);
        buf[read_bytes - 1] = '\0';
        char tempbuf[BUFFER_SIZE];
        int k = 0;
        for(int i = read_bytes/2; i < read_bytes; i++, k++) {
            tempbuf[k] = buf[i];
        }
        k-=2;
        for(int i = read_bytes/2; i < read_bytes, k > -1; i++, k--) {
            buf[i] = tempbuf[k];
        }

        if(lseek(fd, 0, SEEK_SET) < 0) {
            printf("Error while moving cursor to beginning of the file\n");
        } else {
            if(write(fd, buf, read_bytes) < 0) {
                printf("Error while writing data to file\n");
            } else {
                printf("Files modified contents:\n%s\n", buf);
            }
        }
    }

    return 0;
}
