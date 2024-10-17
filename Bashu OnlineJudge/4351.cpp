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
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,tot,lst,Max;
ll b[N],c[N],f[N],id[N],Half[N];
struct Tree{
	ll fa,sum,len,fail,color,ch[4];
	void Init(){
		fa=sum=len=fail=color=0;
		memset(ch,0,sizeof(ch));
	}
}t[N];
void Prepare(){
	for(int i=1;i<=tot;i++){
		t[t[i].fa].ch[t[i].color]=0;
	}
	tot=-1;lst=0;Max=0;
	t[0].Init();t[1].Init();
	t[++tot].len=0;t[tot].fail=1;
	t[++tot].len=-1;t[tot].fail=1;
}
void Insert(ll pos){
	ll x=lst,num=id[s[pos]];
	while(s[pos-t[x].len-1]!=s[pos])x=t[x].fail;
	if(!t[x].ch[num]){
		ll y=++tot,p=t[x].fail;t[y].Init();
		t[y].len=t[x].len+2;t[y].fa=x;t[y].color=num;
		while(s[pos-t[p].len-1]!=s[pos])p=t[p].fail;
		t[y].fail=t[p].ch[num];t[x].ch[num]=y;
	}
	t[t[x].ch[num]].sum++;
	lst=t[x].ch[num];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	ll T=read();
	id['A']=0;id['C']=1;
	id['G']=2;id['T']=3;
	while(T--){
		Prepare();
		scanf("%s",s+1);n=strlen(s+1);
		for(ll i=1;i<=n;i++)Insert(i);
		for(ll i=0;i<=tot;i++)Max=max(Max,t[i].len+1);
		for(ll i=1;i<=Max;i++)c[i]=0;
		for(ll i=0;i<=tot;i++)c[t[i].len+1]++;
		for(ll i=1;i<=Max;i++)c[i]+=c[i-1];
		for(ll i=0;i<=tot;i++)b[c[t[i].len+1]--]=i;
		for(ll i=0;i<=tot;i++)Half[i]=t[i].fail;
		for(ll i=tot+1;i>2;i--){
			ll x=b[i];
			while(t[Half[x]].len*2>t[x].len){
				Half[x]=t[Half[x]].fail;
			}
			Half[t[x].fail]=Half[x];
		}
		f[0]=1;
		ll ans=inf;
		for(ll i=3;i<=tot+1;i++){
			ll x=b[i];
			if(t[x].len&1)f[x]=t[x].len;
			else f[x]=min(f[t[x].fa]+1,f[Half[x]]+t[x].len/2-t[Half[x]].len+1);
			ans=min(ans,n-t[x].len+f[x]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}