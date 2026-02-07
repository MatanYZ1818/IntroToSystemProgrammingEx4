#include <string.h>
#include <stdio.h>
#define MAX_INPUT_LEN 100

int main() {
    char input[MAX_INPUT_LEN];
    char temp;
    FILE* fptr;
    NODE* l1, l2;
    printf("Please enter the string:\n");
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[strlen(input)] == '\n') {
        input[strlen(input)] = '0';
        printf("end corrected. now its %c", input[strlen(input)]);
    }

    if ((fptr = fopen("1.dat", "ab")) == NULL) {
        printf("error opening file");
        return 0;
    }
    fwrite(&input, sizeof(char), strlen(input), fptr);
    fclose(fptr);
    if ((fptr = fopen("1.dat", "rb")) == NULL) {
        printf("error opening file");
        return 0;
    }
    for (int i = 0; i < strlen(input); i++) {
        fread(&temp, sizeof(char), 1, fptr);
        for (int i = 7; i >= 0; --i)
        {
            putchar((temp & (1 << i)) ? '1' : '0');
        }
        printf("\n");
    }

    fclose(fptr);
    return 0;
}