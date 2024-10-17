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
const ll INF=0x3f3f3f3f3f3f3f3f;
const int inf=0x3f3f3f3f;
const int Maxn=(1<<12)+5;
const int N=1e6+5;
const int M=13;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<ll,int>id;
vector<ll>b[N];
ll n,K,G,tot,cnt,Sta,a[N],w[N],P[M],val[N],g[Maxn],f[M][Maxn];
void Divide(ll n){
	for(ll i=2;1ll*i*i<=n;i++){
		if(n%i==0){P[++tot]=i;while(n%i==0)n/=i;}
	}
	if(n!=1)P[++tot]=n;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)w[i]=read();
	G=a[1];
	for(int i=2;i<=n;i++)G=__gcd(G,a[i]);
	if(G==1){puts("0");return 0;}
	Divide(G);Sta=(1<<tot)-1;
	for(int i=1;i<=n;i++){
		ll tmp=1,x=a[i];
		for(int j=1;j<=tot;j++){
			while(x%P[j]==0){x/=P[j];tmp*=P[j];}
		}
		if(!id[tmp])val[id[tmp]=++cnt]=tmp;
		b[id[tmp]].push_back(w[i]);
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int t=1;t<=cnt;t++){
		sort(b[t].begin(),b[t].end());
		for(int S=0;S<=Sta;S++){
			ll tmp=1,x=val[t];
			for(int j=1;j<=tot;j++){
				if(!((S>>(j-1))&1))continue;
				while(x%P[j]==0){x/=P[j];tmp*=P[j];}
			}
			g[S]=tmp;
		}
		for(auto p:b[t]){
			bool flag=false;
			for(int i=tot-1;i>=0;i--){
				for(int S=0;S<=Sta;S++){
					if(f[i][S]==INF)continue;
					int sta=Sta^S;
					for(int T=sta;T;T=(T-1)&sta){
						if(g[T]<=K&&f[i+1][S|T]>f[i][S]+p){
							f[i+1][S|T]=f[i][S]+p;
							flag=true;
						}
					}
				}
			}
			if(!flag)break;
		}
	}
	ll Ans=INF;
	for(int i=1;i<=tot;i++)if(f[i][Sta]!=INF)Ans=min(Ans,f[i][Sta]*i);
	printf("%lld",(Ans==INF?-1:Ans));
	return 0;
}
