#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>

#define BUFFER_SIZE 1024
#define FILENAME "lab2_task1.txt"

typedef struct Number Number;

struct Number {
    int decimalValue;
    int decimalLength;
    char binaryValue[BUFFER_SIZE];
    int binaryLength;
    int position;
};

int stringToNumber(char* stringNumber) {
    int temp = 0;
    for(int i = 0; i < strlen(stringNumber); i++) {
        temp = temp*10 + (stringNumber[i] - '0');
    }
    return temp;
}

char tempBinaryString[BUFFER_SIZE];
void decimalToBinary(int decimal) {
    memset(tempBinaryString, 0, sizeof(tempBinaryString));
    int q = 0;
    int i = 0;
    while(decimal > 0) {
        q = decimal % 2;
        tempBinaryString[i] = q + '0';
        decimal /= 2;
        i++;
    }
    char buff;
    for(int i=0, k = strlen(tempBinaryString) - 1; i<strlen(tempBinaryString)/2; i++, k--) {
        buff = tempBinaryString[i];
        tempBinaryString[i] = tempBinaryString[k];
        tempBinaryString[k] = buff;
    }
}

void append(char* s, char c)
{
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

int main() {
    char *filename = FILENAME;
    int fd = open(filename, O_RDWR);

    char buf[BUFFER_SIZE];
    int read_bytes = read(fd, buf, BUFFER_SIZE);
    if(read_bytes < 0) {
        printf("Error while reading data from file.\nCreate file named \"lab2_task1.txt\" and try again\n");
    } else {
        // Count quantity of numbers in file
        int numsQuantity = 0;
        for(int i=0; i<read_bytes; i++) {
            if(buf[i] >= '0' && buf[i] <= '9') {
                numsQuantity++;
                while(i < read_bytes && buf[i] >= '0' && buf[i] <= '9') {
                    i++;
                }
            }
        }

        // Separate numbers from text
        Number numbers[numsQuantity];
        int numsCounter = 0;
        char temp[BUFFER_SIZE];
        int k = 0;
        for(int i=0; i<read_bytes; i++) {
            memset(temp, 0, sizeof(temp));
            if(buf[i] >= '0' && buf[i] <= '9') {
                Number num;
                num.position = i;
                k = 0;
                while(i < read_bytes && buf[i] >= '0' && buf[i] <= '9') {
                    temp[k] = buf[i];
                    i++;
                    k++;
                }
                num.decimalLength = strlen(temp);
                num.decimalValue = stringToNumber(temp);
                numbers[numsCounter++] = num;
            }
        }

        // Convert numbers to binary
        for(int i=0; i<numsQuantity; i++) {
            decimalToBinary(numbers[i].decimalValue);
            memset(numbers[i].binaryValue, 0, sizeof(numbers[i].binaryValue));
            strcpy(numbers[i].binaryValue, tempBinaryString);
        }
        // Build final string
        numsCounter = 0;
        char finalString[BUFFER_SIZE*2];
        memset(finalString, 0, sizeof(finalString));
        for(int i=0; i<read_bytes; i++) {
            if(buf[i] >= '0' && buf[i] <= '9') {
                strcat(finalString, numbers[numsCounter].binaryValue);
                i += numbers[numsCounter].decimalLength - 1;
                numsCounter++;
            } else {
                append(finalString, buf[i]);
            }
        }
        if(lseek(fd, 0, SEEK_SET) < 0) {
            printf("Error while moving cursor to beginning of the file\n");
        } else {
            if(write(fd, finalString, strlen(finalString)) < 0) {
                printf("Error while writing data to file\n");
            } else {
                printf("Files modified contents:\n%s\n", finalString);
            }
        }
    }

    return 0;
}