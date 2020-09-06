#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char secret[16];

int get_content_length(char *a)
{
    while (*(a++) != '=');
    return atoi(a);
}

/*
 * argv[30] -> CONTENT_LENGTH 
 * */
int main(int argc, char **argv)
{
    printf("\r\n"); 
    char c;
    char buf[256];
    int padd1 = 0;
    int secret_addr = 0x601080;
    int padd2 = 0;
    int flag = open("./flag", O_RDONLY);
    if (flag < 0) {
        printf("Tell the staff flag is gone!\n");
        exit(0);
    }
    read(flag, secret, 16);

    int content_length = get_content_length(argv[30]);
    if (content_length > 256) {
        printf("No no no");
        exit(0);
    }

    for (int i = 0; i < content_length; i++)
        scanf("%c", &buf[i]);

    printf(buf);


    return 0;
}
