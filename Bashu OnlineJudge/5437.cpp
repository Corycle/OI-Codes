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
const ll Mod=1e9+7;
const ll N=205;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N][N],b[N][N];
ll n,m,L,root=1,tot=1;
ll len1[N],len2[N],f[N][N];
struct Tree{ll ch[27],fail,flag;}t[N];
struct Matrix{ll a[N][N];}E,G,F;
void Insert(ll num){
	ll p=root;
	for(ll i=1;i<=len2[num];i++){
		ll c=b[num][i]-'a'+1;
		if(!t[p].ch[c])t[p].ch[c]=++tot;
		p=t[p].ch[c];
	}
	t[p].flag=1;
}
void Build(){
	queue<ll>q;q.push(root);
	while(q.size()){
		ll x=q.front();q.pop();
		if(t[t[x].fail].flag)t[x].flag=1;
		for(ll i=1;i<=26;i++){
			ll y=t[x].ch[i];
			if(!y)continue;
			if(t[x].flag)t[y].flag=1;
			ll p=t[x].fail;q.push(y);
			while(p&&!t[p].ch[i])p=t[p].fail;
			if(p)t[y].fail=t[p].ch[i];
			else t[y].fail=root;
		}
	}
}
ll Check(ll p,ll num){
	for(ll i=1;i<=len1[num];i++){
		ll c=a[num][i]-'a'+1;
		while(p&&!t[p].ch[c])p=t[p].fail;
		if(p)p=t[p].ch[c];
		else p=root;
		if(t[p].flag)return 0;
	}
	return p;
}
void Solve(){
	f[0][root]=1;
	for(ll i=1;i<=L;i++){
		for(ll j=1;j<=n;j++){
			if(i<len1[j])continue;
			for(ll k=1;k<=tot;k++){
				if(t[k].flag)continue;
				ll p=Check(k,j);
				if(p){
					f[i][p]=(f[i][p]+f[i-len1[j]][k])%Mod;
				}
			}
		}
	}
}
void Prepare(){
	F.a[1][tot+1]=1;
	for(ll i=1;i<=tot;i++)G.a[tot+i][i]=1;
	for(ll i=1;i<=tot;i++){
		if(t[i].flag)continue;
		for(ll j=1;j<=n;j++){
			if(len1[j]!=1)continue;
			ll p=i,x=a[j][1]-'a'+1;
			
			while(p&&!t[p].ch[x])p=t[p].fail;
			if(!p)p=root;else p=t[p].ch[x];
			if(!t[p].flag)G.a[tot+i][tot+p]++;
		}
	}
	for(ll i=1;i<=tot;i++){
		if(t[i].flag)continue;
		for(ll j=1;j<=n;j++){
			if(len1[j]!=2)continue;
			ll p=i,x=a[j][1]-'a'+1,y=a[j][2]-'a'+1;
			
			while(p&&!t[p].ch[x])p=t[p].fail;
			if(!p)p=root;else p=t[p].ch[x];
			if(t[p].flag)continue;
			
			while(p&&!t[p].ch[y])p=t[p].fail;
			if(!p)p=root;else p=t[p].ch[y];
			if(!t[p].flag)G.a[i][tot+p]++;
		}
	}
	for(ll i=1;i<=tot*2;i++)E.a[i][i]=1;
}
Matrix Multi(Matrix A,Matrix B){
	memset(f,0,sizeof(f));
	for(ll i=1;i<=tot*2;i++){
		for(ll j=1;j<=tot*2;j++){
			for(ll k=1;k<=tot*2;k++){
				f[i][j]=(f[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	for(ll i=1;i<=tot*2;i++){
		for(ll j=1;j<=tot*2;j++){
			A.a[i][j]=f[i][j];
		}
	}
	return A;
}
int main(){
//	freopen("sorcery.in","r",stdin);
//	freopen("sorcery.out","w",stdout);
	n=read();m=read();L=read();
	for(ll i=1;i<=n;i++){
		scanf("%s",a[i]+1);
		len1[i]=strlen(a[i]+1);
	}
	for(ll i=1;i<=m;i++){
		scanf("%s",b[i]+1);
		len2[i]=strlen(b[i]+1);
		Insert(i);
	}
	Build();
	ll ans=0;
	if(L<=100){
		Solve();
		for(ll i=1;i<=tot;i++){
			ans=(ans+f[L][i])%Mod;
		}
	}
	else{
		Prepare();
		while(L){
			if(L&1)E=Multi(E,G);
			G=Multi(G,G);
			L>>=1;
		}
		F=Multi(F,E);
		for(ll i=1;i<=tot;i++){
			ans=(ans+F.a[1][tot+i])%Mod;
		}
	}
	printf("%lld",ans);
	return 0;
}