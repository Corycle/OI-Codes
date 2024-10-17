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
const ll Mod=10007;
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Trie{
	ll ch[30],fail,flag;
	void Init(){
		fail=flag=0;
		memset(ch,0,sizeof(ch));
	}
}t[N*N];
struct Matrix{
	ll n,m,a[N][N];
	void Clean(){
		n=m=0;
		memset(a,0,sizeof(a));
	}
}F,G;
Matrix Multi(Matrix A,Matrix B){
	Matrix C;C.Clean();
	C.n=A.n;C.m=B.m;
	for(ll i=1;i<=C.n;i++){
		for(ll j=1;j<=C.m;j++){
			for(ll k=1;k<=A.m;k++){
				C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%Mod)%Mod;
			}
		}
	}
	return C;
}
Matrix Matrix_Pow(Matrix A,Matrix B,ll y){
	Matrix ans=A,tot=B;
	while(y){
		if(y&1)ans=Multi(ans,tot);
		tot=Multi(tot,tot);
		y>>=1;
	}
	return ans;
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

char s[N];
ll n,m,tot,Ans,root;
void Prepare(){
	Ans=0;
	tot=root=1;
	t[1].Init();
}
void Insert(){
	ll p=root,len=strlen(s+1);
	for(ll i=1;i<=len;i++){
		ll x=s[i]-'A'+1;
		if(!t[p].ch[x]){
			t[p].ch[x]=++tot;
			t[tot].Init();
		}
		p=t[p].ch[x];
	}
	t[p].flag=1;
}
void Build(){
	queue<ll>q;
	for(ll i=1;i<=26;i++){
		if(t[root].ch[i]){
			q.push(t[root].ch[i]);
			t[t[root].ch[i]].fail=root;
		}
		else t[root].ch[i]=root;
	}
	while(q.size()){
		ll x=q.front();q.pop();
		for(ll i=1;i<=26;i++){
			ll y=t[x].ch[i];
			if(y){
				q.push(y);
				t[y].fail=t[t[x].fail].ch[i];
				if(t[t[y].fail].flag)t[y].flag=1;
			}
			else t[x].ch[i]=t[t[x].fail].ch[i];
		}
	}
}
void DP(){
	F.Clean();F.n=1;F.m=tot;
	G.Clean();G.n=tot;G.m=tot;
	for(ll i=1;i<=tot;i++){
		for(ll j=1;j<=tot;j++){
			for(ll k=1;k<=26;k++){
				if(t[i].ch[k]==j&&!t[j].flag)G.a[i][j]++;
			}
		}
	}
	F.a[1][1]=1;
	Matrix ans=Matrix_Pow(F,G,m);
	for(ll i=1;i<=tot;i++){
		Ans=(Ans+ans.a[1][i])%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%lld%lld",&n,&m)!=EOF){
		Prepare();
		for(ll i=1;i<=n;i++){
			scanf("%s",s+1);
			Insert();
		}
		ll ans=Pow(26,m);
		Build();DP();
		printf("%lld\n",(ans-Ans+Mod)%Mod);
	}
	return 0;
}