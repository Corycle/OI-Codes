#include<cstdio>  
#include<iostream>  
#include<cmath>  
#include<algorithm>  
using namespace std;  
int L,s,t,m;  
int s2=0,e=0,p[2000],p1[2000],f[30000];  
int main(){  
    int i,j;  
    scanf("%d",&L);  
    scanf("%d%d%d",&s,&t,&m);  
    for(i=1;i<=m;i++){  
        scanf("%d",&p[i]);  
    }  
    if(s==t){  
        for(i=1;i<=m;i++)if(p[i]%t==0)e++;  
        cout<<e;  
        return 0;  
    }  
    sort(p+1,p+m+1);
    for(i=1;i<=m;i++){
        if(p[i]-p[i-1]>t){  
            s2+=p[i]-p[i-1]-t;
            }  
        p1[p[i]-s2]=1;  
    }  
    L=p[m]-s2;  
    for(i=1;i<=L+t;i++){  
        f[i]=0xffff;  
        for(j=i-s;j>=i-t&&j>=0;j--){  
            if(f[j]<f[i])f[i]=f[j];  
        }  
        f[i]+=p1[i];  
    }  
    for(i=L,e=0xffff;i<L+t;i++)  
     if(e>f[i])e=f[i];  
    cout<<e;  
    return 0;  
}  