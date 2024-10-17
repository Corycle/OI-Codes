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
ll Ans;
int n,m,cnt,Root;
int h[N],c[N],v[N],root[N];
struct edge{int to,next;}d[N*2];
struct Tree{int l,r,dis,num;ll sum,data;}t[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Pushup(int x){
	t[x].num=t[t[x].l].num+t[t[x].r].num+1;
	t[x].sum=t[t[x].l].sum+t[t[x].r].sum+t[x].data;
}
int Merge(int x,int y){
	if(!x||!y)return x|y;
	if(t[x].data<t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	if(t[x].r)t[x].dis=t[t[x].r].dis+1;
	else t[x].dis=0;Pushup(x);
	return x;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;DFS(y);
		root[x]=Merge(root[x],root[y]);
	}
	while(t[root[x]].sum>m&&t[root[x]].num){
		root[x]=Merge(t[root[x]].l,t[root[x]].r);
	}
	Ans=max(Ans,1ll*t[root[x]].num*v[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int fa=read();
		if(fa)Add(fa,i);
		else Root=i;
		c[i]=read();
		v[i]=read();
		root[i]=i;t[i].num=1;
		t[i].sum=t[i].data=c[i];
	}
	DFS(Root);
	printf("%lld",Ans);
	return 0;
}