#include <stdio.h>

int s_atoi(char *str){
    int sol=0;
    int temp;

    while(*str != '\0'){
        temp = *str-48;
        sol*=10;
        sol+=temp;
        str++;
    }
    return sol;
}

int main(int argc, char **argv){
    printf("%d\n",s_atoi(argv[argc-1]));
    return 0;
}
