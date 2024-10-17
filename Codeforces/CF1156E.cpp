/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],vis[N];
void Solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	Solve(l,mid);Solve(mid+1,r);
	for(int L=mid,R=mid+1,Max=0;L>=l;L--){Max=max(Max,a[L]);while(R<=r&&a[R]<Max)vis[a[R++]]=1;Ans+=vis[Max-a[L]];}
	for(int i=l;i<=r;i++)vis[a[i]]=0;
	for(int L=mid,R=mid+1,Max=0;R<=r;R++){Max=max(Max,a[R]);while(L>=l&&a[L]<Max)vis[a[L--]]=1;Ans+=vis[Max-a[R]];}
	for(int i=l;i<=r;i++)vis[a[i]]=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Solve(1,n);
	printf("%d\n",Ans);
	return 0;
}
