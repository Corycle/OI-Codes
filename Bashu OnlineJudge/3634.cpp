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
const int Mod=59393;
const int N=6e4+5;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Ans;
int a[M][M],fac[N],inv[N];
struct Point{int x,y;}P[M];
bool cmp(Point A,Point B){return A.x!=B.x?A.x<B.x:A.y<B.y;}
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<Mod;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=2;i<Mod;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<Mod;i++)inv[i]=1ll*inv[i-1]*inv[i]%Mod;
}
int C(int n,int m){return n<m?0:(max(n,m)<Mod?1ll*fac[n]*inv[m]%Mod*inv[n-m]%Mod:1ll*C(n/Mod,m/Mod)*C(n%Mod,m%Mod)%Mod);}
int Calc(int x,int y){int ans=0;for(int i=0;i<=min(x,y);i++)ans=mod(ans+1ll*C(x+y-i,i)*C(x+y-i*2,x-i)%Mod);return ans;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	P[0]=(Point){0,0};P[K+1]=(Point){n,m};
	for(int i=1;i<=K;i++){P[i].x=read()-1;P[i].y=read()-1;}
	sort(P+1,P+K+1,cmp);Prepare();
	for(int i=0;i<=K+1;i++){
		for(int j=i;j<=K+1;j++){
			if(P[i].x>P[j].x||P[i].y>P[j].y)continue;
			a[i][j]=Calc(P[j].x-P[i].x,P[j].y-P[i].y);
		}
	}
	int Sta=(1<<K)-1;
	for(int S=0;S<=Sta;S++){
		int lst=0,num=0,ans=1;
		for(int i=1;i<=K;i++)if((S>>(i-1))&1){ans=1ll*ans*a[lst][i]%Mod;num++;lst=i;}
		ans=1ll*ans*a[lst][K+1]%Mod;
		Ans=mod(Ans+1ll*ans*(num&1?Mod-1:1)%Mod);
	}
	printf("%d",Ans);
	return 0;
}