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
const ll inf=0x3f3f3f3f;
const ll N=2000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char op[3],s[N*5];
ll n,m,cnt,tot=1,lst=1,root=1;
ll f[N],sum[N],pos[N],len[N];
ll h[N],fa[N],vis[N],ch[N][4];
struct edge{ll to,next,data;}d[N];
void Add(ll x,ll y,ll z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void SAM(int num){
	ll x=lst,fx=++tot;len[fx]=len[x]+1;
	while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
	if(!x)fa[fx]=root;
	else{
		ll y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			ll fy=++tot;len[fy]=len[x]+1;
			for(ll i=1;i<=3;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
void DFS(ll x){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS(y);
		sum[x]+=sum[y];
	}
}
void Update(ll x){
	if(x==1||vis[x])return;
	vis[x]=1;
	Update(fa[x]);
	f[x]+=f[fa[x]];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	pos[root]=lst;
	for(ll i=2;i<=n;i++){
		ll prt=read();scanf("%s",op);
		lst=pos[prt];SAM(op[0]-'a'+1);
		pos[i]=lst;sum[lst]=1;
	}
	for(ll i=2;i<=tot;i++)Add(fa[i],i,0);DFS(root);
	for(ll i=1;i<=tot;i++)f[i]=sum[i]*(len[i]-len[fa[i]]);
	for(ll i=1;i<=tot;i++)Update(i);
	scanf("%s",s+1);m=strlen(s+1);
	ll p=root,Sum=0,tmp=0;
	for(ll i=1;i<=m;i++){
		ll x=s[i]-'a'+1;
		if(ch[p][x]){p=ch[p][x];tmp++;}
		else{
			while(p&&!ch[p][x])p=fa[p];
			if(!p){p=root;tmp=0;}
			else{tmp=len[p]+1;p=ch[p][x];}
		}
		Sum+=f[fa[p]]+sum[p]*(tmp-len[fa[p]]);
	}
	printf("%lld",Sum);
	return 0;
}