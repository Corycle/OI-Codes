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
const ll inf=0x3f3f3f3f;
const ll N=4000005;
const ll M=12;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt,Ans;
ll tot=1,lst=1,root=1;
ll h[N],c[N],fa[N],rd[N];
ll pos[N],len[N],ch[N][M];
struct edge{ll to,next;}d[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void SAM(ll num){
	ll x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		ll y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			ll fy=++tot;len[fy]=len[x]+1;
			for(ll i=1;i<=m;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
void DFS(ll x,ll prt){
	lst=pos[prt];
	SAM(c[x]);pos[x]=lst;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		if(y==prt)continue;
		DFS(y,x);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)c[i]=read()+1;
	for(ll i=1;i<n;i++){
		ll x=read(),y=read();
		Add(x,y);Add(y,x);
		rd[x]++;rd[y]++;
	}
	for(ll i=1;i<=n;i++){
		if(rd[i]==1){
			pos[i]=1;
			DFS(i,i);
		}
	}
	for(ll i=1;i<=tot;i++){
		Ans+=len[i]-len[fa[i]];
	}
	printf("%lld",Ans);
	return 0;
}