#include <stdio.h>  
#include <string.h>  
long j[11][11];  
long a[11] = {1,1,2,6,24,120,720,5040,40320,362880,3628800};  
  
int main(){  
    memset(j,0,sizeof(j));  
    j[1][1] = 1;  
    int r,n;  
    scanf("%d%d",&n,&r);  
    for(int i=2;i<=n;i++){  
        for(int k = 1;k<=r;k++){  
            j[i][k] = j[i-1][k-1] + j[i-1][k] * k;  
        }  
    }  
    printf("%ld\n",j[n][r] * a[r]);  
    return 0;  
}