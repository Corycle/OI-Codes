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
struct node{
    int l,r;
}a[2000005];
bool cmp(node c,node d){
	if(c.l!=d.l)return c.l<d.l;
	return c.r<d.r;
}
int n,ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
    n=read();
    for(i=1;i<=n;i++){
        int x,w;
        x=read();w=read();
        a[i].l=x-w;
        a[i].r=x+w;
    }
    sort(a+1,a+n+1,cmp);
    for(i=n;i>=1;i--){
        int len=i;
        ans++;
        while(i-1<=n&&a[len].l<a[i-1].r)i--;
    } 
    printf("%d",ans);
	return 0;
}
