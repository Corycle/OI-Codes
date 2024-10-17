#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m,ans;
int zhi[100001];
bool bz[100001],az[1000005];
int main(){
    for(int i=2;i<=sqrt(100000);i++){
        if(!bz[i]){
            for(int j=2;j<=100000/i;j++){
                bz[i*j]=1;
            }
        }
    }
    for(int i=2;i<=100000;i++)if(!bz[i])zhi[++zhi[0]]=i;
    cin>>n>>m;
    for(int i=1;i<=zhi[0];i++){
        for(int j=max(n/zhi[i],1);j<=m/zhi[i];j++){
            if(j==1)continue;
            if(j*zhi[i]<n)continue;
            az[zhi[i]*j-n]=1;
        }
    }
    for(int i=n-n;i<=m-n;i++){
        if(!az[i])++ans;
    }
    printf("%d\n",ans);
    return 0;
}