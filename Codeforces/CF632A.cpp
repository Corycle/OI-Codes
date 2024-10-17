#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
    int s=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
    return s*f;
}
long long n,p,ans,num;
string a[50];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
    int i,j,k;
    n=read();p=read()/2;
    for(i=n;i>=1;i--)cin>>a[i];
    for(i=1;i<=n;i++){
        num*=2;
        if(a[i]=="halfplus")num++;
        ans+=num;
    }
    ans*=p;
    printf("%lld",ans);
    return 0;
}
