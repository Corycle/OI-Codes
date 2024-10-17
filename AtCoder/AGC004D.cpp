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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,cnt,a[N],h[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int DFS(int x){
	int ans=0;
	for(int i=h[x];i;i=d[i].next)ans=max(ans,DFS(d[i].to)+1);
	if(ans==m-1&&a[x]!=1){Ans++;return -1;}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	a[1]=read();Ans=(a[1]!=1);a[1]=1;
	for(int i=2;i<=n;i++)Add(a[i]=read(),i);
	DFS(1);
	printf("%d\n",Ans);
	return 0;
}
