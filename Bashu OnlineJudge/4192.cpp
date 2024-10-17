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
const int N=1e7+5;
const int M=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N],vst[N];
int n,cnt,Ans,Max,a[M];
int sum[N],inv[N],pos[N],prime[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	inv[0]=inv[1]=1;
	for(int i=2;i<=maxn;i++){
		inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
		if(!vis[i]){prime[++cnt]=i;pos[i]=cnt;sum[cnt]=1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int Calc(int p,int num){return 1ll*(Pow(p,num+1)-1)*inv[p-1]%Mod;}
void Update(int &x,int i){
	int p=prime[i],num=0;vst[i]=1;
	while(x%p==0){num++;x/=p;}
	sum[i]=1ll*sum[i]*Calc(p,num)%Mod;
}
void Divide(int x){
	for(int i=1;1ll*prime[i]*prime[i]<=x&&i<=cnt;i++){
		if(x%prime[i]==0)Update(x,i);
	}
	if(x!=1)Update(x,pos[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)Max=max(Max,a[i]=read());
	Prepare(Max);
	for(int i=1;i<=n;i++)Divide(a[i]);
	Ans=1;
	for(int i=1;i<=cnt;i++){
		int p=prime[i];
		if(!vst[i])continue;
		int dlt=1ll*(p-1)*inv[p]%Mod*(sum[i]-1)%Mod+1;
		Ans=1ll*Ans*dlt%Mod;
	}
	printf("%d",(Ans%Mod+Mod)%Mod);
	return 0;
}