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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int B=1000;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N],F[N];
int n,m,cnt=1,tot,Ans;
unordered_map<int,int>vis[N];
int a[N],b[N],h[N],fa[N],top[N],num[N];
struct edge{int to,next,flag;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x],0};
	h[x]=cnt;
}
void DFS(int x){
	b[x]=b[fa[x]];
	if(num[b[fa[x]]]==B){
		b[x]=++tot;top[tot]=x;
		G[b[fa[x]]].push_back(b[x]);
	}
	num[b[x]]++;
	F[b[x]].push_back(a[x]);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
	}
}
void Calc(int x,int val){
	Ans+=(F[x].end()-upper_bound(F[x].begin(),F[x].end(),val));
	for(auto y:G[x])if(!vis[x][y])Calc(y,val);
}
void Solve(int x,int val){
	Ans+=(a[x]>val);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||d[i].flag)continue;
		if(b[x]==b[y])Solve(y,val);
		else Calc(b[y],val);
	}
}
void Split(int x,int p){
	F[p].erase(lower_bound(F[p].begin(),F[p].end(),a[x]));
	F[tot].push_back(a[x]);num[tot]++;b[x]=tot;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||d[i].flag)continue;
		if(b[y]==p)Split(y,p);
		else{
			vis[p][b[y]]=vis[b[y]][p]=1;
			G[tot].push_back(b[y]);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	num[0]=B;DFS(1);
	for(int i=1;i<=tot;i++)sort(F[i].begin(),F[i].end());
	m=read();
	while(m--){
		int op=read();
		if(op==0){
			int x=read()^Ans,y=read()^Ans;
			Ans=0;
			if(x==top[b[x]])Calc(b[x],y);
			else Solve(x,y);
			printf("%d\n",Ans);
		}
		if(op==1){
			int x=read()^Ans,y=read()^Ans;
			F[b[x]].erase(lower_bound(F[b[x]].begin(),F[b[x]].end(),a[x]));
			F[b[x]].insert(lower_bound(F[b[x]].begin(),F[b[x]].end(),y),y);
			a[x]=y;
		}
		if(op==2){
			int x=read()^Ans,y=read()^Ans;
			n++;fa[n]=x;a[n]=y;b[n]=b[fa[n]];
			Add(fa[n],n);Add(n,fa[n]);
			if(num[b[fa[n]]]==B){
				b[n]=++tot;top[tot]=n;
				G[b[fa[n]]].push_back(b[n]);
			}
			num[b[n]]++;
			F[b[n]].insert(lower_bound(F[b[n]].begin(),F[b[n]].end(),a[n]),a[n]);
		}
		if(op==3){
			int x=read()^Ans;
			if(b[x]!=b[fa[x]])vis[b[fa[x]]][b[x]]=vis[b[x]][b[fa[x]]]=1;
			else{top[++tot]=x;Split(x,b[fa[x]]);sort(F[tot].begin(),F[tot].end());}
			for(int i=h[fa[x]];i;i=d[i].next){
				if(d[i].to==x){d[i].flag=d[i^1].flag=1;break;}
			}
			fa[x]=0;
		}
	}
	return 0;
}