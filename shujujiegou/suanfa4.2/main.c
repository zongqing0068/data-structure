#include <stdio.h>
#include <stdlib.h>


float sum(float a[2][8], int i, int j){
    float s = 0;
    int k;
    for(k=i+1; k<=j;k++) s += a[0][k];
    for(k=i; k<=j; k++) s += a[1][k];
    return s;
}

void myfill(float a[2][8], float b[8][8], int c[8][8], int m, int n){
    if(m==n) b[m][n]=a[1][m];
    int k;
    float cost;
    for(k=m;k<n;k++){
        cost=b[m][k]+b[k+1][n]+sum(a, m, n);
        if(cost < b[m][n]) {
            b[m][n]=cost;
            c[m][n]=k;
        }
    }
}

int main()
{
    float a[2][8] = {0,0.04,0.06, 0.08, 0.02, 0.1, 0.12, 0.14, 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    float b[8][8];
    int c[8][8] = {0};
    int i, j;
    for(i=0;i<8;i++){
        for(j=i;j<8;j++){
            b[i][j]=10;
        }
    }


    for(i=0; i<8; i++){
        for(j=0 ;j<8-i;j++)
            myfill(a, b, c, j, j+i);
    }

    for(i=0;i<8;i++){
        for(j=i;j<8;j++){
            printf("%f ", b[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}

