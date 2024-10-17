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
int n,a[201],f[20001],b[201];
int main(){
    int i,j,k,l,s;
    cin>>n;
    for(i=1;i<=n;i++)cin>>a[i];
    for(i=1;i<=n;i++)cin>>b[i];
    cin>>k;
    for(i=1;i<=k;i++)f[i]=0xfffff;
    for(i=1;i<=n;i++)
        for(j=1;j<=b[i];j++){
            l=j*a[i];
            for(s=k;s>=l;s--){
                f[s]=min(f[s],f[s-l]+j);
            }
        }
    cout<<f[k];
    return 0;
}