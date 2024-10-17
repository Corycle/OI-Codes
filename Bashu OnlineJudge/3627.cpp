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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],b[N],p[N],cnt[N],nxt[N],Ans[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Init(){for(int i=1;i<=m;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=m;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[read()]=i;
	for(int i=1;i<=m;i++)b[i]=p[i]=read();
	sort(p+1,p+m+1);
	for(int i=1;i<=m;i++)b[i]=lower_bound(p+1,p+m+1,b[i])-p;
	for(int i=1;i<=n;i++){tree.Add(a[i],1);cnt[i]=tree.Ask(a[i]);}
	tree.Init();
	for(int i=2,lst=2,j=0;i<=n;i++){
		tree.Add(a[i],1);
		while(j>0&&tree.Ask(a[i])!=cnt[j+1]){
			while(lst<i-nxt[j])tree.Add(a[lst++],-1);
			j=nxt[j];
		}
		if(tree.Ask(a[i])==cnt[j+1])j++;
		nxt[i]=j;
	}
	tree.Init();
	for(int i=1,lst=1,j=0;i<=m;i++){
		tree.Add(b[i],1);
		while(j>0&&(j==n||tree.Ask(b[i])!=cnt[j+1])){
			while(lst<i-nxt[j])tree.Add(b[lst++],-1);
			j=nxt[j];
		}
		if(tree.Ask(b[i])==cnt[j+1])j++;
		if(j==n)Ans[++Ans[0]]=i-n+1;
	}
	printf("%d\n",Ans[0]);
	for(int i=1;i<=Ans[0];i++)printf("%d ",Ans[i]);
	return 0;
}