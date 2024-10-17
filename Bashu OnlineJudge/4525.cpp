#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int s[100005][2],sum[100005][2],c[100005],x[100005];
int n,m,ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>x[i];
    for(int i=1;i<=n;i++){
        cin>>c[i];
        s[c[i]][i%2]++;
        sum[c[i]][i%2]=(sum[c[i]][i%2]+x[i])%10007;
    }
    for(int i=1;i<=n;i++)
        ans=(ans+i*((s[c[i]][i%2]-2)*x[i]%10007+sum[c[i]][i%2]))%10007;
    cout<<ans;
    return 0;
}