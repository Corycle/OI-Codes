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
const ll Mod=1e9+7;
const ll N=2005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char S[N],s[N];
ll c[N],f[N][N];
ll n,m,tot=1,root=1;
struct Tree{ll ch[10],flag,fail;}t[N];
void Insert(){
	ll len=strlen(s+1),p=root;
	for(ll i=1;i<=len;i++){
		ll x=s[i]-'0';
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].flag=1;
}
void Build(){
	queue<ll>q;q.push(root);
	while(q.size()){
		ll x=q.front();q.pop();
		if(t[t[x].fail].flag)t[x].flag=1;
		for(ll i=0;i<=9;i++){
			ll y=t[x].ch[i];
			if(!y)continue;q.push(y);
			if(t[x].flag)t[y].flag=1;
			ll p=t[x].fail;
			while(p&&!t[p].ch[i])p=t[p].fail;
			if(p)t[y].fail=t[p].ch[i];
			else t[y].fail=root;
		}
	}
}
ll GetPos(ll x,ll c){
	while(x&&!t[x].ch[c])x=t[x].fail;
	if(x)x=t[x].ch[c];else x=root;
	return x;
}
ll DFS(ll len,ll pos,ll Zero,ll flag){
	if(len==n+1)return !Zero;
	if(!flag&&f[len][pos]!=-1)return f[len][pos];
	ll k=(flag?c[len]:9),ans=0,nxt=0;
	for(ll i=0;i<=k;i++){
		ll t1=Zero&(i==0),t2=flag&(i==k);
		nxt=GetPos(root,i);
		if(Zero&&!t[nxt].flag){
			ans=(ans+DFS(len+1,nxt,t1,t2))%Mod;
		}
		nxt=GetPos(pos,i);
		if(!Zero&&!t[nxt].flag){
			ans=(ans+DFS(len+1,nxt,t1,t2))%Mod;
		}
	}
	if(!flag&&!Zero)f[len][pos]=ans;
	return ans;
}
ll Solve(){
	memset(f,-1,sizeof(f));
	for(ll i=1;i<=n;i++)c[i]=S[i]-'0';
	return DFS(1,1,1,1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",S+1);
	n=strlen(S+1);m=read();
	for(ll i=1;i<=m;i++){
		scanf("%s",s+1);
		Insert();
	}
	Build();
	printf("%lld",Solve());
	return 0;
}