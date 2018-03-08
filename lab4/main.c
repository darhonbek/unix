#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main() {
    struct stat st = {0};

    if (stat("/home/darhonbek/u1510429", &st) == -1) {
        mkdir("/home/darhonbek/u1510429", 0777);
        if (stat("/home/darhonbek/u1510429/Darkhonbek", &st) == -1) {
            mkdir("/home/darhonbek/u1510429/Darkhonbek", 0777);
            if (stat("/home/darhonbek/u1510429/Darkhonbek/Mamataliev", &st) == -1) {
                mkdir("/home/darhonbek/u1510429/Darkhonbek/Mamataliev", 0777);
            }
        }
    }

    char *filename = "/home/darhonbek/u1510429/Darkhonbek/Mamataliev/file.txt";
    int fd = open(filename, O_CREAT, S_IRWXO | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    FILE *fp = fopen(filename, "a");
    if (fd > -1) {
        symlink("/home/darhonbek/u1510429/Darkhonbek/Mamataliev/", "/home/u1510429/Darkhonbek/Mamataliev/file.txt");
        symlink("/home/darhonbek/u1510429/Darkhonbek/", "/home/u1510429/Darkhonbek/Mamataliev/file.txt");
        symlink("/home/darhonbek/u1510429/", "/home/u1510429/Darkhonbek/Mamataliev/file.txt");
        symlink("/home/darhonbek/", "/home/u1510429/Darkhonbek/Mamataliev/file.txt");

        const long int id = 29;

        // 1
        double ans = 0, alpha = 0;
        printf("Enter value of Alpha: ");
        scanf("%lf", &alpha);
        ans = pow((1 + id), alpha);
        fprintf(fp, "1: %lf\n", ans);

        // 2
        ans = pow(M_E, id);
        fprintf(fp, "2: %lf\n", ans);

        // 3
        ans = sin(id);
        fprintf(fp, "3: %lf\n", ans);

        // 4
        ans = cos(id);
        fprintf(fp, "4: %lf\n", ans);

        // 5
        ans = log(1 + id);
        fprintf(fp, "5: %lf\n", ans);

        // 6
        ans = atan(id);
        fprintf(fp, "6: %lf\n", ans);

        // 7
        ans = log(1 - id);
        fprintf(fp, "7: %lf\n", ans);

        // 8
        ans = asinh(id);
        fprintf(fp, "8: %lf\n", ans);

        // 9
        ans = log((1 + id)/(1 - id));
        fprintf(fp, "9: %lf\n", ans);

        // 10
        ans = 1/(1 - id);
        fprintf(fp, "10: %lf\n", ans);

        fclose(fp);
    }

    return 0;
}
