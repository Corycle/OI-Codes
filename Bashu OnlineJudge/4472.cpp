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
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=600005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,cnt,tot=1,lst=1,root=1;
ll a[N],h[N],fa[N],len[N],sum[N],pos[N];
ll Min[N],Max[N],Ans1[N],Ans2[N],ch[N][30];
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
			for(ll i=1;i<=26;i++)ch[fy][i]=ch[y][i];
			fa[fy]=fa[y];fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
		}
	}
	lst=fx;
}
void DFS(ll x){
	sum[x]=pos[x]?1:0;
	Min[x]=pos[x]?a[pos[x]]:inf;
	Max[x]=pos[x]?a[pos[x]]:-inf;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS(y);
		Ans1[len[x]]+=sum[x]*sum[y];
		if(Min[x]!=inf&&Min[y]!=inf)Ans2[len[x]]=max(Ans2[len[x]],Min[x]*Min[y]);
		if(Max[x]!=-inf&&Max[y]!=-inf)Ans2[len[x]]=max(Ans2[len[x]],Max[x]*Max[y]);
		Min[x]=min(Min[x],Min[y]);
		Max[x]=max(Max[x],Max[y]);
		sum[x]+=sum[y];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);
	for(ll i=n;i>=1;i--){
		SAM(s[i]-'a'+1);
		pos[lst]=i;
	}
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=tot;i++)Add(fa[i],i);
	for(ll i=0;i<=tot;i++)Ans2[i]=-inf;
	DFS(root);
	for(ll i=n;i>=0;i--){
		Ans1[i]+=Ans1[i+1];
		Ans2[i]=max(Ans2[i],Ans2[i+1]);
	}
	for(ll i=0;i<n;i++){
		printf("%lld %lld\n",Ans1[i],Ans2[i]==-inf?0:Ans2[i]);
	}
	return 0;
}