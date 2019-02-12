// It is a tricky way to do it, but I took a lot of references from
// https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define Error 1
#define SIZE 100

int main(int argc, char *argv[]){

    if(argc == 2){
       int fd_1 = open(argv[1], O_RDONLY);
       if (fd_1 < 0){
            printf("Couldn't open file:  %s\n", argv[1]);
            return Error;
       } else {
            int sz; 
            char *c = (char *) calloc(200, sizeof(char)); 
            sz = read(fd_1, c, SIZE); 
            printf(c); 

            while (read(fd_1, c, SIZE) != 0) {
                printf("%s", c);
            }
       }

    close(fd_1);
        
    } else if (argc == 3){
        int fd_1 = open(argv[1], O_RDONLY);
        int fd_2 = open("dummy.txt", O_WRONLY | O_CREAT, 0644);

        if (fd_1 < 0){
            printf("Couldn't open file:  %s\n", argv[1]);
            return Error;
        }else{
            int sz; 
            char *c = (char *) calloc(200, sizeof(char)); 
            sz = read(fd_1, c, SIZE); 

            while ( read(fd_1, c, SIZE) != 0) {
                write(fd_2, c, SIZE); 
            }
        }
        close(fd_1);
        close(fd_2);
    }
}




