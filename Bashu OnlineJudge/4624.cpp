#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=500005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
vector<ll>p[N];
ll n,tot,ans,cnt;
ll fa[N],id[N],sum[N];
struct Trie{ll ch[30],id;}t[N];
ll Find(ll x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool cmp(ll x,ll y){
	return sum[x]<sum[y];
}
void Insert(ll num){
	ll p=0,len=strlen(s+1);
	for(ll i=len;i>=1;i--){
		ll x=s[i]-'a'+1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].id=num;
}
void DFS1(ll x){
	for(ll i=1;i<=26;i++){
		ll y=t[x].ch[i];
		if(!y)continue;
		if(!t[y].id)fa[y]=Find(x);
		else p[t[Find(x)].id].push_back(t[y].id);
		DFS1(y);
	}
}
void DFS2(ll x){
	sum[x]=1;
	ll num=p[x].size();
	for(ll i=0;i<num;i++){
		DFS2(p[x][i]);
		sum[x]+=sum[p[x][i]];
	}
	sort(p[x].begin(),p[x].end(),cmp);
}
void DFS3(ll x){
	id[x]=++cnt;
	ll num=p[x].size();
	for(ll i=0;i<num;i++){
		DFS3(p[x][i]);
		ans+=id[p[x][i]]-id[x];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		scanf("%s",s+1);
		Insert(i);
	}
	for(ll i=1;i<=tot;i++)fa[i]=i;
	DFS1(0);DFS2(0);DFS3(0);
	printf("%lld",ans);
	return 0;
}