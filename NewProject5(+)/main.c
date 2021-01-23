#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int i, nbytes;
long long ch;

void decision(long long ch,int nbytes)
{
    printf("Ch = %d\n", ch);
    for (i = 0; i < nbytes; i++){
        ch = ch << 8;
    }
    printf("Ch(modif) = %d\n", ch);
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		ch = atoll(argv[1]);
		nbytes = atoi(argv[2]);
		decision(ch, nbytes);
	} else {
		printf("Error!\n");
		exit(-1);
	}
	return 0;
}
