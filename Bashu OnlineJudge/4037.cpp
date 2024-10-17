#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll tot=1,lst=1,root=1,ans,cnt;
ll ch[N][30],fa[N],len[N],c[N],h[N],vis[N];
struct edge{
	ll to,next;
}d[N];
void Addedge(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void SAM(ll num){
	ll x=lst,fx=++tot;
	len[fx]=len[x]+1;
	while(x&&!ch[x][num]){
		ch[x][num]=fx;
		x=fa[x];
	}
	if(!x)fa[fx]=root;
	else{
		ll y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			ll fy=++tot;
			len[fy]=len[x]+1;
			for(ll i=1;i<=26;i++){
				ch[fy][i]=ch[y][i];
			}
			fa[fy]=fa[y];
			fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){
				ch[x][num]=fy;
				x=fa[x];
			}
		}
	}
	lst=fx;
	vis[lst]=1;
}
void DFS(ll x){
	if(vis[x])c[x]=1;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;
		DFS(y);
		ans-=2*len[x]*c[x]*c[y];
		c[x]+=c[y];
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	ll n=strlen(s+1);
	ans=(1+n)*n*(n-1)/2;
	for(ll i=n;i>=1;i--){
		SAM(s[i]-'a'+1);//转前缀 
	}
	for(ll i=2;i<=tot;i++){
		Addedge(fa[i],i);
	}
	DFS(1);
	printf("%lld",ans);
	return 0;
}