/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,id1,id2,Min,cnt;
int a[N],b[N],h[N],dep[N],p[N][M],g[N][M];
struct edge{int to,next,data;}d[N*2];
bool cmp(int x,int y){return a[x]<a[y];}
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
}
struct Trie{
	int tot;
	struct Tree{
		int id,ch[2];
		void Init(){id=ch[0]=ch[1]=0;}
	}t[N*20];
	void Init(){t[tot=1].Init();}
	void Insert(int x){
		int p=1;
		for(int i=30;i>=0;i--){
			int c=(a[x]>>i)&1;
			if(!t[p].ch[c])t[t[p].ch[c]=++tot].Init();
			p=t[p].ch[c];
		}
		t[p].id=x;
	}
	void Query(int x){
		int p=1;
		for(int i=30;i>=0;i--){
			int c=(a[x]>>i)&1;
			if(t[p].ch[c])p=t[p].ch[c];
			else p=t[p].ch[c^1];
		}
		int y=t[p].id;
		if(Min>(a[x]^a[y])){
			Min=(a[x]^a[y]);
			id1=x;id2=y;
		}
	}
}tree;
void Divide(int l,int r,int len){
	if(l>=r)return;
	if(len<0){
		for(int i=l;i<r;i++){
			Add(b[i],b[i+1],0);
			Add(b[i+1],b[i],0);
		}
		return;
	}
	int cnt0=0,cnt1=0;
	for(int i=l;i<=r;i++){
		if(((a[b[i]]>>len)&1)==0)cnt0++;
		if(((a[b[i]]>>len)&1)==1)cnt1++;
	}
	if(cnt0&&cnt1){
		Min=inf;tree.Init();
		for(int i=l;i<l+cnt0;i++)tree.Insert(b[i]);
		for(int i=l+cnt0;i<=r;i++)tree.Query(b[i]);
		Ans+=Min;Add(id1,id2,Min);Add(id2,id1,Min);
	}
	Divide(l,l+cnt0-1,len-1);
	Divide(r-cnt1+1,r,len-1);
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==p[x][0])continue;
		p[y][0]=x;
		g[y][0]=d[i].data;
		DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=max(g[i][j-1],g[p[i][j-1]][j-1]);
			}
		}
	}
}
int Ask(int x,int y){
	int Max=0;
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y]){
			Max=max(Max,g[x][k]);x=p[x][k];
		}
	}
	if(x==y)return Max;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){
			Max=max(Max,g[x][k]);x=p[x][k];
			Max=max(Max,g[y][k]);y=p[y][k];
		}
	}
	return max(Max,max(g[x][0],g[y][0]));
}
int main(){
//	freopen("fight.in","r",stdin);
//	freopen("fight.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=i;
	sort(b+1,b+n+1,cmp);
	Divide(1,n,30);
	DFS(1,1);ST();
	printf("%lld\n",Ans);
	while(m--){
		int x=read(),y=read(),z=read();
		if(y==p[x][0]||x==p[y][0]){
			int dlt1=(a[x]^a[y]);
			int dlt2=(a[x]^a[y])&z;
			printf("%lld\n",Ans-dlt1+dlt2);
		}
		else{
			int dlt1=Ask(x,y);
			int dlt2=(a[x]^a[y])&z;
			printf("%lld\n",min(Ans,Ans-dlt1+dlt2));
		}
	}
	return 0;
}