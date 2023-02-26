#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

int change_judge(int *bills, int length);

int change_judge(int *bills, int length){
    int changes[2] = {0};//分别代表手中5、10、20美元零钱的数目
    int i;
    for(i=0;i<length;i++){
        if(bills[i] == 5) changes[0]++;
        else if(bills[i] == 10){
            changes[1]++;
            changes[0]--;
        }
        else{
            changes[2]++;
            if(changes[1] > 0){
                changes[1]--;
                changes[0]--;
            }
            else changes[0] -= 3;
        }
        if(changes[0] < 0 || changes[1] < 0) return FALSE;
    }
    return TRUE;
}


int main()
{
    int bills[5] = {5,5,5.10,20};
    printf("%d", change_judge(bills, 5));
    return 0;
}
