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
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=1e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
char s[3][N];
int Lim[3],cnt[4],fac[N],inv[N],sum[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=0;i<3;i++){
		Lim[i]=n-read()-1;scanf("%s",s[i]+1);
		if(Lim[i]<0){printf("%d",Pow(2,n));return 0;}
	}
	for(int i=1;i<=n;i++){
		int x=s[0][i]-'0',y=s[1][i]-'0',z=s[2][i]-'0';
		y^=x;z^=x;cnt[y<<1|z]++;
	}
	int w=0,h=0;
	for(int c0=0;c0<=cnt[0];c0++){
		for(int c1=0;c1<=cnt[1];c1++){
			int x=c0+c1,y=c0+cnt[1]-c1;
			if(x>Lim[0]||x>Lim[1]||y>Lim[2])continue;
			w=max(w,x);h=max(h,y);
			sum[x][y]=mod(sum[x][y]+1ll*C(cnt[0],c0)*C(cnt[1],c1)%Mod);
		}
	}
	for(int i=0;i<=w;i++){
		for(int j=0;j<=h;j++){
			if(i)sum[i][j]=mod(sum[i][j]+sum[i-1][j]);
			if(j)sum[i][j]=mod(sum[i][j]+sum[i][j-1]);
			if(i&&j)sum[i][j]=mod(sum[i][j]-sum[i-1][j-1]+Mod);
		}
	}
	for(int c2=0;c2<=cnt[2];c2++){
		for(int c3=0;c3<=cnt[3];c3++){
			int x=min(Lim[0]-c2-c3,Lim[1]-(cnt[2]-c2)-(cnt[3]-c3)),y=Lim[2]-c2-(cnt[3]-c3);
			if(x<0||y<0)continue;
			x=min(x,w);y=min(y,h);
			Ans=mod(Ans+1ll*sum[x][y]*C(cnt[2],c2)%Mod*C(cnt[3],c3)%Mod);
		}
	}
	printf("%d",mod(Pow(2,n)-Ans+Mod));
	return 0;
}