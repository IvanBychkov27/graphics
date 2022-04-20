/*
        gcc sin.c -o sin -lm
        ./sin
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265

int main(void)
{
    double d = PI / 3;
    printf("d   = %f\n", d);

    double res;
    res = sin(d);
    printf("sin = %f\n", res);

    char numbers[][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."};

    char *msg;
    msg = (char*)malloc(5);
    int i, idx, data;
    int n[5];

    data = 10000*PI;

    for (i = 5; i > 0; i--){
        n[i] = data % 10;
        data = data / 10;
    }

     for (i = 0; i < 5; i++){
       strcat(msg, numbers[n[i]]);
     }

    printf("msg  = %s\n", msg);

    return 0;
}