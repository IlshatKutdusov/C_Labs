#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int answer = 1, i, j, k, n, inputanswer, outputanswer;
double f = 1.0;

void decision(i, outputanswer) {
    j = i;
    double **a, **b, **c;
    a = (double**)malloc(i * sizeof(double*));
    b = (double**)malloc(i * sizeof(double*));
    c = (double**)malloc(i * sizeof(double*));
    for (k = 0; k < i; k++){
        a[k] = (double*)malloc(i * sizeof(double));
        b[k] = (double*)malloc(i * sizeof(double));
        c[k] = (double*)malloc(i * sizeof(double));
    }

    for (k = 0; k < i; k++) {
        for (n = 0; n < j; n++) {
            *(*(a + k) + n) = f;
            f++;
        }
    }
    for (k = 0; k < i; k++) {
        for (n = 0; n < j; n++) {
            if (n >= k) {
                *(*(b + k) + n) = *(*(a + k) + n);
                *(*(c + k) + n) = -*(*(a + k) + n);
            } else {
                *(*(b + k) + n) = *(*(a + n) + k);
                *(*(c + k) + n) = *(*(a + k) + n);
            }
        }
    }

    outputf(a, b, c);
}
void outputf(double **a, double **b, double **c) {
    if (outputanswer == 0) {
        printf("Answer(b):\n");
        for (k = 0; k < i; k++) {
            for (n = 0; n < j; n++) {
                printf("%g ", b[k][n]);
            }
            printf("\n");
            free(b[k]);
        }
        printf("Answer(c):\n");
        for (k = 0; k < i; k++) {
            for (n = 0; n < j; n++) {
                printf("%g ", c[k][n]);
            }
            printf("\n");
            free(c[k]);
        }
    } else {
        FILE *outputfile;
        outputfile = fopen("outputfile.txt", "w");
        fprintf(outputfile, "Answer(b):\n");
        for (k = 0; k < i; k++) {
            for (n = 0; n < j; n++) {
                fprintf(outputfile, "%g ", b[k][n]);
            }
            fprintf(outputfile, "\n");
            free(b[k]);
        }
        fprintf(outputfile, "Answer(c):\n");
        for (k = 0; k < i; k++) {
            for (n = 0; n < j; n++) {
                fprintf(outputfile, "%g ", c[k][n]);
            }
            fprintf(outputfile, "\n");
            free(c[k]);
        }
        fclose(outputfile);
    }
    free(a);
    free(b);
    free(c);
}

int main() {
    printf("Hello user!\n");
    while (answer != 0) {
        printf("Select options:\n");
        printf("Input - Console(0) or File(1)\n");
        scanf("%d", &inputanswer);
        printf("Output - Console(0) or File(1)\n");
        scanf("%d", &outputanswer);
        if (inputanswer == 0) {
            printf("Write i (i>=1)\n");
            scanf("%d", &i);
            decision(i, outputanswer);
        } else {
            FILE *inputfile;
            inputfile = fopen("inputfile.txt", "r");
            fscanf(inputfile, "%d", &i);
            fclose(inputfile);
            decision(i, outputanswer);
            return 0;
        }
        printf("Do the word again? - No(0) or Yes(1)\n");
        scanf("%d", &answer);
    }
    return 0;
}
