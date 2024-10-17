#include<stdio.h>  
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int n;  
long long f[10000];  
int main(){  
    scanf("%d",&n);  
    for(int i=1;i<=n;i++) f[i]=i;  
    for(int i=1;i<n;i++){  
        bool flag=0;  
        for(int j=1;flag==0;j++){  
            int to=i+j*i;  
            if(to>n){  
                to=n;  
                flag=1;  
            }  
            f[to]=min(f[to],f[i]+5+j*2);  
        }  
    }  
    printf("%lld",f[n]);  
}  