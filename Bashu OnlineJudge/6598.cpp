/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int M=1005;
const int N=35;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,tot,Ans,Num;
int p[N],a[N][N],vis[N][N],C[M][M],f[M],inv[M];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=0;i<maxn;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=mod(C[i-1][j-1]+C[i-1][j]);}
	for(int i=1;i<maxn;i++)for(int j=1;j<=i;j++)f[i]=mod(f[i]+inv[j]);
}
int main(){
//	freopen("sing.in","r",stdin);
//	freopen("sing.out","w",stdout);
	int T=read();Prepare(1e3);
	while(T--){
		memset(a,0,sizeof(a));
		n=read();m=read();Ans=Num=tot=0;
		for(int i=1;i<=n;i++){
			scanf("%s",s+1);
			int len=strlen(s+1);Num+=len;
			for(int j=1;j<=len;j++)a[i][s[j]-'a']=1;
		}
		scanf("%s",s+1);
		if(n==m){
			Ans=1ll*f[n]*Num%Mod;
			printf("%d\n",Ans);
			continue;
		}
		int flag=0;
		for(int i=1;i<=n-m+1;i++){
			flag=1;
			for(int j=1;j<=m;j++)if(!a[i+j-1][s[j]-'a'])flag=0;
			if(flag)p[++tot]=i;
		}
		if(!tot){puts("-1");continue;}
		int Sta=(1<<tot)-1;
		for(int S=1;S<=Sta;S++){
			int cnt=0,sum=0;
			memset(vis,0,sizeof(vis));
			for(int i=1;i<=tot;i++)cnt+=(S>>(i-1))&1;
			for(int i=1;i<=tot;i++){
				if(!((S>>(i-1))&1))continue;
				for(int j=1;j<=m;j++)vis[p[i]+j-1][s[j]-'a']=1;
			}
			for(int i=1;i<=n;i++){
				for(int j=0;j<26;j++)sum+=vis[i][j];
			}
			Ans=mod(Ans+1ll*f[sum]*Num%Mod*(cnt&1?1:Mod-1)%Mod);
		}
		printf("%d\n",Ans);
	}
	return 0;
}