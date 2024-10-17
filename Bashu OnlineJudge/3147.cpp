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
//struct _{};
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long n,m,a,b,k;
int Tpow(int x,int p){  //快速幂计算(a^n)*(b^m)
    long long tmp=x,ans=1;
    while(p>0){
        if(p&1)ans=(ans*tmp)%10007;
        tmp=(tmp*tmp)%10007;
        p>>=1;
    }
    return ans;
}
long long h[1005][1005];
int main(){
    scanf("%lld%lld%lld%lld%lld",&a,&b,&k,&n,&m);
    h[1][1]=1;
    for(int i=2;i<=k+1;i++)  //暴力构造杨辉三角，别学我
        for(int j=1;j<=i;j++)
            h[i][j]=(h[i-1][j-1]+h[i-1][j])%10007;
    long long s=(h[k+1][n+1]%10007*(Tpow(a,n)%10007)*(Tpow(b,m)%10007))%10007;
    printf("%lld",s);
    return 0;
}