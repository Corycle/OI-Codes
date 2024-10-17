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
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char S[N];
string s[N];
ll n,K,tot=1,lst=1,root=1;
ll f[N],b[N],c[N],fa[N];
ll rd[N],len[N],vis[N],ch[N][30];
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
void Solve(){
	for(ll i=1;i<=n;i++){
		ll Len=s[i].length(),p=root;
		for(ll j=0;j<Len;j++){
			p=ch[p][s[i][j]-'a'+1];ll x=p;
			while(x&&vis[x]!=i){
				vis[x]=i;rd[x]++;x=fa[x];
			}
		}
	}
	rd[root]=0;
	for(ll i=1;i<=tot;i++)c[len[i]]++;
	for(ll i=1;i<=tot;i++)c[i]+=c[i-1];
	for(ll i=tot;i>=1;i--)b[c[len[i]]--]=i;
	for(ll i=1;i<=tot;i++){
		if(rd[b[i]]<K)f[b[i]]=f[fa[b[i]]];
		else f[b[i]]=f[fa[b[i]]]+len[b[i]]-len[fa[b[i]]];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(ll i=1;i<=n;i++){
		lst=root;
		scanf("%s",S);
		s[i]=(string)(S);
		ll Len=s[i].length();
		for(ll j=0;j<Len;j++){
			SAM(s[i][j]-'a'+1);
		}
	}
	Solve();
	for(ll i=1;i<=n;i++){
		ll x=root,ans=0;
		ll Len=s[i].length();
		for(ll j=0;j<Len;j++){
			x=ch[x][s[i][j]-'a'+1];
			ans+=f[x];
		}
		printf("%lld ",ans);
	}
	return 0;
}