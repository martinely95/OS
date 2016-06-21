#include <stdio.h> //printf
#include <unistd.h> //execl, execlp
#include <sys/types.h> // fork, getpid, getppid
#include <sys/wait.h> // wait
#include <stdlib.h> // exit
#include <fcntl.h>  // O_WRONLY|O_CREAT|O_TRUNC
#include <string.h> // strcpy


main(int argc, char* argv[]){

    const int STDIN = 0;
    const int STDOUT = 1;
    const int STDERR = 2;

    // we run the wrapper without arguments
    if (argc == 1) {
       
        int fd1;
        int i;
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
            //да бъде посредник за играта (да я стартира и да изчаква нейното приключване):
            if ( execl("./tic-tac-toe.sh", "tic-tac-toe", NULL) == -1 ) {
                exit(99);
            }
        }

        wait(&status);
        returned_status = status / 256;

        // vzemame log failovete sortirani i go slagame vav faila temp
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
                dup2(fd1, STDOUT);
                execlp("ls", "ls", "./.tic-tac-toe", "-t", NULL);
            }          
        }
        
        // we create a file, we have to wait
        wait(&status);
        returned_status = status / 256;

        // vzemame imeto na log faila
        char logFileName[64];


        //vzemame imeto na horata ot log faila
        char ime1[64];
        char ime2[64];


        int name = 0;
        if (( fd1=open("temp", O_RDONLY) ) == -1) {
            write(2, "Operation open failed!\n", sizeof("Operation open failed!\n")-1);
            exit(99);
        }

        i=0;
        int name2 = 0;
        char c[2] = " \0";
        while ( read(fd1, &c, 1) ) {
            // byte == int
            if (c[0] != '-' && name == 0) {
                ime1[i] = c[0];
                logFileName[i] = c[0];
            }
            else if (c[0] == '-' && name == 0) {
                ime1[i] = '\0';
                logFileName[i] = c[0];
                name = i;
            }
            else if (c[0] != '-' && name2 == 0) {
                ime2[i-name-1] = c[0];
                logFileName[i] = c[0];
            }
            else if (c[0] == '-' && name2 == 0 && c[0] != '\n' ) {
                ime2[i-name-1] = '\0';
                logFileName[i] = c[0];
                name2 = 1;
            }
            else if (c[0] != '-' && name2 > 0 && c[0] != '\n' ){
                logFileName[i] = c[0];
            }
            else { 
                logFileName[i] = '\0';
                break;
            }
            i++;
        }

        close(fd1);

        // vzemame obsh broj igri
        int fd[2];//,  // file descriptors for the pipe, nbytes which are read from the pipe
        pipe(fd);

        // grep na pobedi i remita
        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            chdir("./.tic-tac-toe");

            close(fd[STDIN]); //close the side of the pipe that will not be used

            dup2(fd[STDOUT], STDOUT);

            execlp("grep", "grep", "Печели\\|реми", logFileName, NULL);       
        }

        close(fd[STDOUT]);

        // wc na redovete varnati ot grep

        int fd2[2]; // this is where the fun starts
        pipe(fd2);
        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        int nbytes;
        char readbuffer[4096];

        if (father == 0)  // child
        {
            close(fd2[STDIN]); 

            dup2(fd[STDIN], STDIN);
            dup2(fd2[STDOUT], STDOUT);

            execlp("wc", "wc", "-l", NULL);       
        }

        close(fd2[STDOUT]);
        close(fd[STDIN]); 

        readbuffer[0]='\0';
        nbytes = read(fd2[STDIN], readbuffer, sizeof(readbuffer));

        char *n4 = strrchr(readbuffer, '\n');
        if (n4)
            *n4 = 0;

        char * allGamesCount = malloc(nbytes+1); 
        strcpy(allGamesCount, readbuffer);
        
        wait(&status);
        returned_status = status / 256;

        close(fd2[STDIN]); 

        // masovo kopirane na kod
        // do not do this at home

        pipe(fd);

        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            chdir("./.tic-tac-toe");

            close(fd[STDIN]); //close the side of the pipe that will not be used

            dup2(fd[STDOUT], STDOUT);

            execlp("grep", "grep", "реми", logFileName, NULL);       
        }

        close(fd[STDOUT]);

        // wc na redovete varnati ot grep
        pipe(fd2);
        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            close(fd2[STDIN]); 

            dup2(fd[STDIN], STDIN);
            dup2(fd2[STDOUT], STDOUT);

            execlp("wc", "wc", "-l", NULL);       
        }

        close(fd2[STDOUT]);
        close(fd[STDIN]); 

        readbuffer[0]='\0';
        nbytes = read(fd2[STDIN], readbuffer, sizeof(readbuffer));

        char *n3 = strrchr(readbuffer, '\n');
        if (n3)
            *n3 = 0;

        char * remiCount = malloc(nbytes+1); 
        strcpy(remiCount, readbuffer);

        wait(&status);
        returned_status = status / 256;

        close(fd2[STDIN]); 

        // masovo kopirane na kod2
        // do not do this at home

        pipe(fd);

        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            chdir("./.tic-tac-toe");

            close(fd[STDIN]); //close the side of the pipe that will not be used

            dup2(fd[STDOUT], STDOUT);

            char * grepString = malloc(strlen(ime1)+strlen("Печели ")+1); 
            strcpy(grepString, "Печели ");
            strcat(grepString, ime1);

            execlp("grep", "grep", grepString, logFileName, NULL);       
        }

        close(fd[STDOUT]);

        // wc na redovete varnati ot grep
        pipe(fd2);
        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            close(fd2[STDIN]); 

            dup2(fd[STDIN], STDIN);
            dup2(fd2[STDOUT], STDOUT);

            execlp("wc", "wc", "-l", NULL);       
        }

        close(fd2[STDOUT]);
        close(fd[STDIN]); 

        readbuffer[0]='\0';
        nbytes = read(fd2[STDIN], readbuffer, sizeof(readbuffer));

        char *n1 = strrchr(readbuffer, '\n');
        if (n1)
            *n1 = 0;
        char * win1 = malloc(nbytes+1); 
        strcpy(win1, readbuffer);
        
        wait(&status);
        returned_status = status / 256;

        close(fd2[STDIN]); 


        // masovo kopirane na kod3
        // i daje raboti
        // do not do this at home
        pipe(fd);

        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            chdir("./.tic-tac-toe");

            close(fd[STDIN]); //close the side of the pipe that will not be used

            dup2(fd[STDOUT], STDOUT);

            char * grepString = malloc(strlen(ime1)+strlen("Печели ")+1); 
            strcpy(grepString, "Печели ");
            strcat(grepString, ime2);

            execlp("grep", "grep", grepString, logFileName, NULL);       
        }

        close(fd[STDOUT]);

        // wc na redovete varnati ot grep
        pipe(fd2);
        if((father = fork()) == -1)
        {
            perror("fork");
            exit(1);
        }

        if (father == 0)  // child
        {
            close(fd2[STDIN]); 

            dup2(fd[STDIN], STDIN);
            dup2(fd2[STDOUT], STDOUT);

            execlp("wc", "wc", "-l", NULL);       
        }

        close(fd2[STDOUT]);
        close(fd[STDIN]); 

        readbuffer[0]='\0';
        nbytes = read(fd2[STDIN], readbuffer, sizeof(readbuffer));

        char *n2 = strrchr(readbuffer, '\n');
        if (n2)
            *n2 = 0;
        char * win2 = malloc(nbytes+1); 
        strcpy(win2, readbuffer);
        
        wait(&status);
        returned_status = status / 256;

        close(fd2[STDIN]); 


        char * logfileFullPath = malloc(strlen("./.tic-tac-toe/")+strlen(logFileName)+1); 
        strcpy(logfileFullPath, "./.tic-tac-toe/");
        strcat(logfileFullPath, logFileName);

        int stdout_copy = dup(STDOUT);

        if( ( fd1 = open(logfileFullPath, O_WRONLY|O_APPEND, 0200 ) ) == -1 ){
            write(2, "Something went wrong!\n", sizeof("Something went wrong!\n")-1);
            exit(99);
        }
        else {                
            dup2(fd1, STDOUT);
        }      

        write(STDOUT, "\n", strlen("\n"));
        write(STDOUT, "Общ брой игри: ", strlen("Общ брой игри: "));
        write(STDOUT, allGamesCount, strlen(allGamesCount));
        write(STDOUT, "\n", strlen("\n"));

        write(STDOUT, ime1, strlen(ime1));
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, win1, strlen(win1));      
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, win2, strlen(win2));      
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, remiCount, strlen(remiCount)); 
        write(STDOUT, "\n", strlen("\n"));

        write(STDOUT, ime2, strlen(ime2));
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, win2, strlen(win2));      
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, win1, strlen(win1));      
        write(STDOUT, " ", strlen(" "));
        write(STDOUT, remiCount, strlen(remiCount)); 
        write(STDOUT, "\n", strlen("\n"));

        dup2(stdout_copy, STDOUT);        

        if (returned_status == 99) {
            exit(99);
        } 
        else if (returned_status == 0) {
            exit(0);
        }
    }
}