int strlen(char *str);
char *stradd(char *origin, char *addition);
int strfind(char *origin, char *substr);

int main(int argc, char **argv){
    
    printf("Initial      : %d\n", strlen(argv[1]));
    printf("New string   : %s\n", stradd(argv[1],argv[2]));

    if(strfind(stradd(argv[1],argv[2]), argv[3]) == 1){
        printf("Was the substring found : yes" );
    }
    else{
        printf("Was the substring found : no" );
    }
}