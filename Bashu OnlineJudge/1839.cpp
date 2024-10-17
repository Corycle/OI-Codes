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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N],vis[N],sum[N],Ans[N];
struct Node{int dep,dis,id;}a[N],b[N];
bool cmp(Node A,Node B){return A.dep>B.dep;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){
	x=Find(x);y=Find(y);
	if(x!=y){
		fa[x]=y;
		sum[y]+=sum[x];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=n;i++)a[i]=(Node){read(),0,i};
	for(int i=1;i<=m;i++)b[i]=(Node){read(),read(),i};
	sort(a+1,a+n+1,cmp);
	sort(b+1,b+m+1,cmp);
	int pos=1,Max=0;
	for(int i=1;i<=m;i++){
		while(pos<=n&&a[pos].dep>b[i].dep){
			int x=a[pos].id;vis[x]=1;
			if(vis[x-1])Union(x,x-1);
			if(vis[x+1])Union(x,x+1);
			Max=max(Max,sum[Find(x)]);
			pos++;
		}
		if(Max<b[i].dis)Ans[b[i].id]=1;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}