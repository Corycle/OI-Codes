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
const ll N=400005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N],b[N];
ll n,cnt,tot=1,lst=1,root=1;
ll h[N],fa[N],sum1[N],sum2[N],len[N],ch[N][27];
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
void DFS1(ll x){
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS1(y);
		sum1[x]+=sum1[y];
	}
}
void DFS2(ll x){
	sum2[x]=sum1[x]*(len[x]-len[fa[x]])+sum2[fa[x]];
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS2(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",a+1);ll len1=strlen(a+1);
	scanf("%s",b+1);ll len2=strlen(b+1);
	for(ll i=1;i<=len1;i++){
		SAM(a[i]-'a'+1);sum1[lst]=1;
	}
	for(ll i=1;i<=tot;i++)Add(fa[i],i);
	ll p=root,Sum=0,Ans=0;
	DFS1(root);DFS2(root);
	for(ll i=1;i<=len2;i++){
		ll x=b[i]-'a'+1;
		while(p&&!ch[p][x])p=fa[p];
		if(!p){p=root;Sum=0;}
		else{
			Sum=min(Sum,len[p])+1;p=ch[p][x];
			Ans+=sum1[p]*(Sum-len[fa[p]])+sum2[fa[p]];
		}
	}
	printf("%lld",Ans);
	return 0;
}