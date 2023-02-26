#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int min_num(int coins[MAX], int amount){
    int length = 0;
    int i, j, flag, min;
    i = flag = 0;
    while(coins[i]){
        length++;
        i++;
    }//求解硬币面额的种类总数（coins数组中除有效面额外，其余数为0）
    int N[amount+1];
    N[0] = 0;
    for(i=1;i<=amount;i++){
        min = MAX;
        for(j=0;j<length;j++){
            if(coins[j] <= i){
                if(N[i-coins[j]] != -1 && N[i-coins[j]] + 1 < min){
                    min = N[i-coins[j]] + 1;
                    flag = 1;
                }
            }
        }
        if(flag) N[i] = min;
        else N[i] = -1;
        flag = 0;
    }
    return N[amount];
}



int main()
{
    int coins[MAX] = {0};
    int i;
    coins[0]=2;
    int n=min_num(coins, 3);
    printf("%d", n);
    return 0;
}
