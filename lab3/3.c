#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#define MAX_NAME_LEN 1024

int main() {
    printf("Enter directory name: ");
    char directoryName[MAX_NAME_LEN];
    scanf("%s", directoryName);

    DIR *directory;
    directory = opendir(directoryName);
    struct dirent* directoryEntry;
    struct stat  state;
    if(directory) {
        printf("Regular files in directory with access permissions for the current user:\n");
        while(directoryEntry = readdir(directory)) {
            lstat(directoryEntry->d_name, &state);
            if(S_ISREG(state.st_mode) &&
                    (state.st_mode & S_IRUSR) &&
                    (state.st_mode & S_IWUSR) &&
                    (state.st_mode & S_IXUSR)
                    ){
                printf("%s\n", directoryEntry->d_name);
            }
        }
    closedir(directory);
    } else {
        printf("Directory could not be opened. Please, make sure you provided correct path and have an access rights.\n");
    }
    return 0;
}
