#include <stdio.h> //printf
#include <unistd.h> //execl, execlp
#include <sys/types.h> // fork, getpid, getppid
#include <sys/wait.h> // wait
#include <stdlib.h> // exit
#include <fcntl.h>  // O_WRONLY|O_CREAT|O_TRUNC



main(int argc, char* argv[]){
    const int STDOUT = 1;
    if (argc == 1) {
        //debugging
        // printf("%s", argv[1]);
        int fd[2], nbytes; // file descriptors for the pipe, nbytes which are read from the pipe
        int fd1;
        char readbuffer[4096]; 
        int i,j;
        int status;
        int returned_status;
        int father;

        if((father = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if (father == 0)  // child
        {
            if ( execl("./tic-tac-toe.sh", "tic-tac-toe", NULL) == -1 ) {
                exit(99);
            }
            exit(0);
        }

        wait(&status);
        returned_status = status / 256;

        //pipe(fd);
        
        if((father = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if (father == 0)  // child
        {

            if( ( fd1 = open("temp", O_WRONLY|O_CREAT|O_TRUNC, 0600 ) ) == -1 ){
                    write(2, "Something went wrong!\n", sizeof("Something went wrong!\n")-1);
                    exit(99);
            }
            else {
                     /* Child process closes up output side of pipe */
                    // close(1);
                    // dup(fd1);
                    dup2(fd1, 1);

                    /* Send "string" through the input side of pipe */
                    //write(fd[0], string, (strlen(string)+1));
                    execlp("ls", "ls", "./.tic-tac-toe", "-t", NULL);
            }          
        }
        //todo: da podam na funkciqta temp faila vmesto pipe
        
        wait(&status);
        returned_status = status / 256;

        // if (fcntl(fd1, F_GETFD)) { // if fd1 is not closed
        //     close(fd1);
        // }
        char logFileDir[256] = "./.tic-tac-toe/";
        pipe(fd);
        if((father = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if (father == 0)  // child
        {

            if( ( fd1 = open("temp", O_RDONLY, 0400 ) ) == -1 ){
                    write(2, "Something went wrong!\n", sizeof("Something went wrong!\n")-1);
                    exit(99);
            }
            else {
                    close(fd[0]);
                    // dup(fd1);
                    dup2(fd[1], 1);

                    /* Send "string" through the input side of pipe */
                    //write(fd[0], string, (strlen(string)+1));
                    execlp("head", "head", "-n", "1", "temp", NULL);
            }          
        }

        if (father > 0) {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                snprintf(logFileDir + 15, 256 - 15, "%s", readbuffer); 
                // printf("Received string: %s", readbuffer);
        }
        printf("Received string: %s", readbuffer);
        printf("Received string: %s", logFileDir);
        wait(&status);
        returned_status = status / 256;

        // if (fcntl(fd1, F_GETFD)) { // if fd1 is not closed
        //     close(fd1);
        // }
        // char ime1[64];
        // char ime2[64];
        // pipe(fd);
        // if((father = fork()) == -1)
        // {
        //         perror("fork");
        //         exit(1);
        // }

        // if (father == 0)  // child
        // {

        //     if( ( fd1 = open("lo", O_RDONLY, 0400 ) ) == -1 ){
        //             write(2, "Something went wrong!\n", sizeof("Something went wrong!\n")-1);
        //             exit(99);
        //     }
        //     else {
        //             close(fd[0]);
        //             // dup(fd1);
        //             dup2(fd[1], 1);

        //             /* Send "string" through the input side of pipe */
        //             //write(fd[0], string, (strlen(string)+1));
        //             execlp("head", "head", "-n", "1", "temp", NULL);
        //     }          
        // }

        // if (father > 0) {
        //         /* Parent process closes up output side of pipe */
        //         close(fd[1]);

        //         /* Read in a string from the pipe */
        //         nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
        //         printf("Received string: %s", readbuffer);
        // }
        
        // wait(&status);
        // returned_status = status / 256;

        if ( father > 0 ){
            //father body
            // status returns the PID 
            
            
            printf("Status of execution of tic-tac-toe: %d\n", returned_status);
            if (returned_status == 99) {
                write(STDOUT, "Unsuccesful opening of file.\n", sizeof("Unsuccesful opening of file.\n")-1);
            } 
            else if (returned_status == 0) {
                write(STDOUT, "Game session ended.\n", sizeof("Game session ended.\n")-1);
            }
        } 
        else {
            //child body
            
        }
    }
}