#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]) {
    const int WRONG_NUMBER_OF_ARGUMENTS = 1;
    const int OPEN_OF_FILE_FAILED = 2;
    const int ERR_OUT = 2;
    const int ST_OUT = 1;

    const int READABLE_CHARS_START = 32;
    const int READABLE_CHARS_END = 127;

    if (argc != 2) {
        write(ERR_OUT,"Йоу, wrong number of arguments!\n", sizeof("Йоу, wrong number of arguments!\n")-1);
        exit(WRONG_NUMBER_OF_ARGUMENTS);
    }

    // file descriptor for the source file
    int fd;
    // open the file
    if (( fd=open(argv[1], O_RDONLY) ) == -1) {
        write(ERR_OUT, "Operation open failed!\n", sizeof("Operation open failed!\n")-1);
        exit(OPEN_OF_FILE_FAILED);
    }

    // buffer for each character (byte) that is read
    char buff;
    // size of the content that is read
    ssize_t read_size;
    // array for all readable characters
    int chars[127] = {0};
    while ( ( read_size=read(fd, &buff, 1) ) > 0 ) {
        // byte == int
        chars[buff] += 1;
    }

    // the actual character behind the byte
    char sym[2]="";
    // end of string for the character
    sym[1]='\0';

    // skip the first 32 (human) unreadable characters
    buff = READABLE_CHARS_START; 
    for (buff; buff<READABLE_CHARS_END; buff++) {
        if (chars[buff] > 0){
            sym[0] = buff;
            printf("Char %s behind byte %d occurs %d times.\n", sym, buff, chars[buff]);
        }
    }

    // close the file
    close(fd);
}