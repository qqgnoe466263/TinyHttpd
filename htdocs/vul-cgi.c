#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char secret[16];

int main(int argc, char **argv)
{
    printf("\r\n"); 
    char c;
    char buf[256];
    int secret_addr = &secret;
    int padd1 = 0;
    int padd2 = 0;
    int flag = open("./flag", O_RDONLY);
    if (flag < 0) {
        printf("Tell the staff flag is gone!\n");
        exit(0);
    }
    read(flag, secret, 16);
    memset(buf, '\x00', 256);

    int content_length = atoi(getenv("CONTENT_LENGTH"));
    if (content_length > 256)
        content_length = 255;

    for (int i = 0; i < content_length; i++)
        scanf("%c", &buf[i]);

    printf(buf);

    return 0;
}
