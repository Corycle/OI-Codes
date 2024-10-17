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
const ll Mod=19930726;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,K,lst,tot=-1,b[N];
struct Tree{ll len,sum,fail,ch[30];}t[N];
void Insert(ll pos){
	ll x=lst,num=s[pos]-'a'+1;
	while(s[pos-t[x].len-1]!=s[pos])x=t[x].fail;
	if(!t[x].ch[num]){
		ll y=++tot,p=t[x].fail;t[y].len=t[x].len+2;
		while(s[pos-t[p].len-1]!=s[pos])p=t[p].fail;
		t[y].fail=t[p].ch[num];t[x].ch[num]=y;
	}
	t[t[x].ch[num]].sum++;
	lst=t[x].ch[num];
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
bool cmp(ll x,ll y){
	return t[x].len>t[y].len;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	scanf("%s",s+1);
	t[++tot].len=0;t[tot].fail=1;
	t[++tot].len=-1;t[tot].fail=1;
	for(ll i=1;i<=n;i++)Insert(i);
	for(ll i=tot;i>=1;i--)t[t[i].fail].sum+=t[i].sum;
	for(ll i=2;i<=tot;i++)if(t[i].len&1)b[++b[0]]=i;
	sort(b+1,b+b[0]+1,cmp);
	ll ans=1;
	for(ll i=1;i<=b[0];i++){
		if(K>t[b[i]].sum){
			ans=ans*Pow(t[b[i]].len,t[b[i]].sum)%Mod;
			K-=t[b[i]].sum;
		}
		else{
			ans=ans*Pow(t[b[i]].len,K)%Mod;
			K=0;break;
		}
	}
	if(K)printf("-1");
	else printf("%lld",ans);
	return 0;
}