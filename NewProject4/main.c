#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int answer = 1, k, i = 0, n, j = 0, v = 1, v2 = 1, c, inputanswer, outputanswer;
FILE *inputfile, *outputfile;
char ch;
char str_in[30];
char str_out[30];

void decision(n, outputanswer) {
    char *a;
    a = (char*)malloc(n * sizeof(char));
    if (inputanswer == 0) {
        getchar();
        printf("Write string:\n");
        for (k = 0; k < n; k++) {
            a[k] = getchar();
        }
    } else {
        for (k = 0; k < n; k++) {
            fscanf(inputfile, "%c", &a[k]);
            printf("next %c\n", a[k]);
        }
    }
    outputf(a);
}
void outputf(char *a) {
    if (outputanswer == 0) {
        printf("Answer:\n");
        k = n-1;
        while (j == 0) {
            if (a[k] == ','){
                printf("%d\n", k);
                j = 100;
            }
            k--;
        }
    } else {
        if (v2 != 0) {
            outputfile = fopen(str_out, "w");
            printf("Out: %s \n", str_out);
        }
        fprintf(outputfile, "Answer:\n");
        k = n-1;
        while (j == 0) {
            if (a[k] == ','){
                fprintf(outputfile, "%d", k);
                j = 100;
            }
            k--;
        }
        fclose(outputfile);
    }
    free(a);
}

int main() {
    printf("Hello user!\n");
    while (answer != 0) {
        v = 1;
        v2 = 1;
        printf("Select options:\n");
        printf("Input - Console(0) or File(1)\n");
        scanf("%d", &inputanswer);
        printf("Output - Console(0) or File(1)\n");
        scanf("%d", &outputanswer);
        if (inputanswer != 0) {
            printf("White path to file:\n");
            printf("Inputfile:\n");
            ch = getche();
            do {
                if (ch != 13) {
                    str_in[i] = ch;
                    i++;
                } else {
                    inputfile = fopen("inputfile.txt", "r");
                    printf("In(basic): inputfile.txt \n");
                    v = 0;
                }
                ch = getche();
            } while (ch != 13);
            if (v != 0) {
                inputfile = fopen(str_in, "r");
                printf("In: %s \n", str_in);
            }
            fscanf(inputfile, "%d", &n);
            fclose(inputfile);
            decision(n, outputanswer);
            return 0;
        }
        if (outputanswer == 1) {
            printf("Outputfile:\n");
            ch = getche();
            i = 0;
            do {
                if (ch != 13) {
                    str_out[i] = ch;
                    i++;
                } else {
                    outputfile = fopen("outputfile.txt", "w");
                    printf("Out(basic): outputfile.txt \n");
                    v2 = 0;
                }
                ch = getche();
            } while (ch != 13);
            printf("Out: %s \n", str_out);
        }
        if (inputanswer == 0) {
            printf("White N (n>=1)\n");
            scanf("%d", &n);
            decision(n, outputanswer);
        }
        printf("Do the word again? - No(0) or Yes(1)\n");
        scanf("%d", &answer);
    }
    return 0;
}
