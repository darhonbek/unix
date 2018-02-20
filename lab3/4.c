#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <time.h>
#define MAX_NAME_LEN 1024

int main() {
    printf("Enter directory name: ");
    char directoryName[MAX_NAME_LEN];
    scanf("%s", directoryName);

    DIR *directory;
    directory = opendir(directoryName);
    struct dirent* directoryEntry;
    struct stat  state;
    long twoDays = 60 * 60 * 24 * 2;
    long accessTime = 0;
    if(directory) {
        printf("Regular files in directory, accessed within last 2 days:\n");
        while(directoryEntry = readdir(directory)) {
            lstat(directoryEntry->d_name, &state);
            if(S_ISREG(state.st_mode)) {
                accessTime = time(NULL) - state.st_atime;
                if (accessTime <= twoDays) {
                    printf("%s \n", directoryEntry->d_name);
                    printf("Access time: %s\n\n", ctime(&state.st_atime));
                }
            }
        }
    } else {
        printf("Directory could not be opened. Please, make sure you provided correct path and have an access rights.\n");
    }
    closedir(directory);
    return 0;
}
