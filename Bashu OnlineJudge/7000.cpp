#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define ll long long
#define re register
#define ull unsigned ll
using namespace std;
inline int read(){
	int s=0,t=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*t;
}
const int N=(1<<25);
char ch[55];
int n,L,U0,U1;
ll Ans,w[55],h[55];
int p[N],f[N],G[N];bool g[N];
int main(){
//	freopen("cows.in","r",stdin);
//	freopen("cows.out","w",stdout);
	n=read();
	for(int i=0;i<25;i++)p[1<<i]=i;
	for(int i=0;i<n;i++){
		scanf("%s",ch);
		for(int j=0;j<n;j++){
			int t=ch[j]-'0';
			if(t)w[i]=w[i]+(1ll<<j),h[j]=h[j]+(1ll<<i);
		}
	}
	for(int i=0;i<n;i++)w[i]=w[i]&h[i];
	L=n/2,U0=(1<<L)-1,U1=(1<<n-L)-1;
	f[0]=1;
	for(int S=1;S<=U0;S++){
		int i=p[S&-S],T=S-(S&-S);
		f[S]=f[T]&((w[i]&T)==T);
	}
	for(re int i=1;i<=U0;i<<=1)
	for(re int j=0;j<=U0;j+=(i<<1))
	for(re int k=0;k<i;++k)f[i+j+k]+=f[j+k];
	
	g[0]=1,G[0]=U0,Ans=f[U0];
	for(re int S=1;S<=U1;S++){
		int i=p[S&-S],T=S-(S&-S);
		g[S]=g[T]&(((w[i+L]>>L)&T)==T);
		if(g[S])G[S]=G[T]&w[i+L],Ans+=f[G[S]];
	}printf("%lld",Ans);
	return 0;
}