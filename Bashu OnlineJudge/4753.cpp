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
const int Mod=998244353;
const int Phi=998244352;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,c,d,q,cnt,Ans[N];
int b[N],mu[N],vis[N],prime[N];
int H[N],F[N],G[N],Fr[N],Gr[N],InvH[N],InvFr[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){prime[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else{mu[i*prime[j]]=0;break;}
		}
	}
}
int main(){
//	freopen("equation.in","r",stdin);
//	freopen("equation.out","w",stdout);
	n=read();Prepare();
	c=read();d=read();q=read();
	for(int i=1;i<=n;i++)H[i]=Pow(i,d);
	for(int i=1;i<=n;i++)InvH[i]=Pow(H[i],Mod-2);
	for(int i=1;i<=n;i++)F[i]=Pow(i,(c-d+Phi)%Phi);
	for(int i=1;i<=n;i++){//Mobius 1
		for(int j=i;j<=n;j+=i){
			Fr[j]=(Fr[j]+1ll*mu[j/i]*F[i]%Mod+Mod)%Mod;
		}
		InvFr[i]=Pow(Fr[i],Mod-2);
	}
	while(q--){
		bool flag=true;
		for(int i=1;i<=n;i++)b[i]=read();
		for(int i=1;i<=n;i++)Gr[i]=Ans[i]=0;
		for(int i=1;i<=n;i++){//Mobius 2
			if(b[i]&&!InvH[i])flag=false;//dlt=b[i]/H[i]
			int dlt=1ll*b[i]*InvH[i]%Mod;
			for(int j=i;j<=n;j+=i){
				Gr[j]=(Gr[j]+1ll*mu[j/i]*dlt%Mod+Mod)%Mod;
			}
			if(Gr[i]&&!InvFr[i])flag=false;//G[i]=Gr[i]/Fr[i]
			G[i]=1ll*Gr[i]*InvFr[i]%Mod;
		}
		for(int i=1;i<=n;i++){//Anti Mobius
			for(int j=i;j<=n;j+=i){
				Ans[i]=(Ans[i]+1ll*mu[j/i]*G[j]%Mod+Mod)%Mod;
			}
			if(Ans[i]&&!H[i])flag=false;//Ans[i]=Ans[i]/H[i]
			Ans[i]=1ll*Ans[i]*InvH[i]%Mod;
		}
		if(!flag)printf("-1\n");
		else{
			for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
			printf("\n");
		}
	}
	return 0;
}