#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>


#define REPORT_FILE "report.txt"

void analizeLog(char *logFile, char *report);

struct logFile{
    char *type;
    char *info[100];
    int id;
};

struct logFile logs[1000];
int possition = 0;

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./dmesg-analizer.o logfile.txt\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void addToStruct(char *type, char *info){

    for(int i = 0; i < possition; i++) {
        if(*logs[i].type == *type) {
            logs[i].info[logs[i].id] = (char *)malloc(sizeof(char)*1000);
            strcpy(logs[i].info[logs[i].id], info);
            logs[i].id++;
            return;
            }
    }
    logs[possition].type = (char *)malloc(sizeof(char)*1000);
    logs[possition].info[0] = (char *)malloc(sizeof(char)*1000);
    strcpy(logs[possition].type, type);
    strcpy(logs[possition].info[0], info);
    logs[possition].id = 1;
    possition++;

}

void checkLines(char *line){
    
    char *t = (char *)malloc(sizeof(char) * 1); 
    char *aux = (char *)malloc(sizeof(char) * 1);
    char *type = (char *)malloc(sizeof(char) * 1000);
    char *buffer = (char *)malloc(sizeof(char) * 1000);
    char *info = (char *)malloc(sizeof(char) * 1000);
    bool flag = true;
    bool found_type = false;
    bool already_checked = false;
    
    for(int i = 0; i < 15; i++) {
        (*t = *line);
        strcat(info, t);
        line++;
    }    

    while((*t = *line) != '\0') {
        *aux = *++line; 
        --line;
        if(*t == ':' && *aux == ' ' && !already_checked) {
            ++line;
            *t = *line;
            strcpy(type, buffer);
            flag = false;
            found_type = true;
            already_checked = true;
        }
        if(flag) {
            strcat(buffer, t);
        }else {
            strcat(info, t);
        }
        ++line;  
    }
    if(!found_type) {
        strcat(type, "General");
        strcat(info, buffer);
    }
    addToStruct(type, info);
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    FILE *fileInput, *fileOutput;
    int c;
    char *f = (char *)malloc(sizeof(char)*1);

    if((fileInput = open(logFile, O_RDONLY)) < 0){
	printf("Cannot open your file");
    }
    
    fileOutput = fopen(report, "w");

    char *line = (char *)malloc(sizeof(char)*1000);

    while((c = read(fileInput, f, 1)) > 0) {
	if( *f == '\n') {
	    strcat(line, "\n\0");
	    checkLines(line);
	    *line = NULL;
	    
	} else {
	    strcat(line, f);
        }
    }

    for(int k = 0; k < possition; k++) {
        fprintf(fileOutput, logs[k].type);
	    fprintf(fileOutput, "\n");
	    write(1, logs[k].type, 100);
	    write(1, "\n", 1);
	
    for(int j = 0; j < logs[k].id; j++) {
	    fprintf(fileOutput, "\t");
	    fprintf(fileOutput, logs[k].info[j]);
	    write(1, "\t", 1);
	    write(1, logs[k].info[j], 500);
        }
    }
    close(fileInput);
    fclose(fileOutput);

    printf("Report is generated at: [%s]\n", report);
}
