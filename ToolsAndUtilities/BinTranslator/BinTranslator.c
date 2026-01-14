/* BinTranslator - Binary to Text File Converter */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 4096 // Optimal buffer size for I/O operations

void error(const char *err) {
    if(errno != 0) perror(err);
    else fprintf(stderr, "[ERROR]: %s\n", err);
    exit(EXIT_FAILURE);
}

/* Data structure to hold input file information. */
typedef struct {
    char INPUT_FILE_BIN[256];
} data;

data readInput(int argc, char **argv);
void Translate(data F_REPO);

int main(int argc, char **argv) {
    data F_REPO = readInput(argc, argv);
    Translate(F_REPO);
    return 0;
}

/* Reads a binary file from command line, validates it and updates the structure. */
data readInput(int argc, char **argv) {
    if(argc != 2) error("Not valid parameters!\nPlease follow the suggestion: ---> \"./BinTranslator <file.bin>\"");

    size_t INPUT_FILE_BIN_LEN = strlen(argv[1]);
    if(INPUT_FILE_BIN_LEN < 5 || strcmp(argv[1] + INPUT_FILE_BIN_LEN - 4, ".bin") != 0) 
        error("Not valid file extension!\nThis program can translate only .bin files to .txt");

    data F_REPO;
    strcpy(F_REPO.INPUT_FILE_BIN, argv[1]);

    return F_REPO;
}

/* Takes the ".bin" file and creates a namesake changing the extension to ".txt". */
void ChangeExtension(const char *INPUT_FILE_BIN_NAME, char *TRANSLATED_FILE_NAME) {
    strcpy(TRANSLATED_FILE_NAME, INPUT_FILE_BIN_NAME);
    char *p = strrchr(TRANSLATED_FILE_NAME, '.');
    if(p) strcpy(p, ".txt");
}

/* Reads binary file in chunks and writes printable characters to text file.
 * Non-printable bytes (except newlines and tabs) are replaced with dots. 
 * Uses buffered I/O for efficiency with large files. */
void Translate(data F_REPO) {
    FILE *FILE_BIN = fopen(F_REPO.INPUT_FILE_BIN, "rb");
    if(!FILE_BIN) error("Unable to open binary file!");

    fseek(FILE_BIN, 0, SEEK_END);
    long FILE_SIZE = ftell(FILE_BIN);
    if(FILE_SIZE == 0) {
        fclose(FILE_BIN);
        error("Binary file is empty!");
    }
    fseek(FILE_BIN, 0, SEEK_SET);

    char TRANSLATED_FILE_NAME[256];
    ChangeExtension(F_REPO.INPUT_FILE_BIN, TRANSLATED_FILE_NAME);

    FILE *FILE_TXT = fopen(TRANSLATED_FILE_NAME, "w");
    if(!FILE_TXT) {
        fclose(FILE_BIN);
        error("Unable to create the \".txt\" file!");
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while((bytes_read = fread(buffer, 1, BUFFER_SIZE, FILE_BIN)) > 0) {
        for(size_t i = 0; i < bytes_read; i++) {
            if(isprint(buffer[i]) || buffer[i] == '\n' || buffer[i] == '\t') {
                fputc(buffer[i], FILE_TXT);               
            } else {
                fputc('.', FILE_TXT);
            }
        }
    }

    fclose(FILE_TXT);
    fclose(FILE_BIN);
    printf("Translation completed: %s --> %s\n", F_REPO.INPUT_FILE_BIN, TRANSLATED_FILE_NAME);
}
