#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void usage();

int main(int argc, char **argv){
    
    if (argc <= 1){
        usage();
        }

	size_t i;
	size_t msg_len = 0;
	
    for (i = 1; i < argc; i++){
		msg_len += strlen(argv[i]) + 1;
	}
	
    char *message;
	message = calloc(msg_len, sizeof(char));
	message[0] = '\0';
	for (i = 1; i < argc; i++) {
		strcat(message, argv[i]);
		strcat(message, " ");
	}
	message[msg_len - 1] = '\n';

	DIR *dir;
	struct dirent *pDirent;
	const char *path = "/dev/pts/";
	const int pathlength = strlen(path);

	dir = opendir(path);

	if (dir == NULL){
		perror("Error directory: ");
		return EXIT_FAILURE;
	}

	char *pathpts;
	size_t c, len;
	int flag = 0;
	int fd;
	i = 0;
	while ((pDirent = readdir(dir)) != NULL){
		len = strlen(pDirent->d_name);

		for (c = pDirent->d_name[i]; i < len; i++){
			if (isdigit(c) != 0) {
				continue;
			} else {
				flag = -1;
				break;
			}
		}
		if (flag == -1){
			flag = 0;
			continue;
		}
		if ((pathpts = calloc((strlen(pDirent->d_name) + pathlength) + 1, sizeof(char))) == NULL){
			perror("Error: ");
		} else {
			pathpts[0] = '\0';
			strcat(pathpts, path);
			strcat(pathpts, pDirent->d_name);
		}
		fd = open(pathpts, O_WRONLY | ENOTTY | ENOLCK | O_TRUNC);
		
        if (fd == -1) {
			perror("Error within file: ");
		}
		write(fd, message, msg_len);
		close(fd);
	}

	closedir(dir);
	return EXIT_SUCCESS;
}

void usage(){
	printf("Broacast a meessage to all PTS terminals.\n");
}
