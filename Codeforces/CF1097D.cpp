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
const int N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n;
int m,Ans,f[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){inv[0]=inv[1]=1;for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;}
int Solve(int p,int num){
	memset(f,0,sizeof(f));f[num]=1;
	for(int k=1;k<=m;k++){
		for(int j=0;j<=num;j++){
			f[j]=1ll*f[j]*inv[j+1]%Mod;
			for(int k=j+1;k<=num;k++)f[j]=mod(f[j]+1ll*f[k]*inv[k+1]%Mod);
		}
	}
	int ans=0;
	for(int i=0,tmp=1;i<=num;i++,tmp=1ll*tmp*p%Mod)ans=mod(ans+1ll*f[i]*tmp%Mod);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=1;Prepare();
	for(int i=2;1ll*i*i<=n;i++){
		if(n%i==0){
			int num=0;
			while(n%i==0){n/=i;num++;}
			Ans=1ll*Ans*Solve(i%Mod,num)%Mod;
		}
	}
	if(n!=1)Ans=1ll*Ans*Solve(n%Mod,1)%Mod;
	printf("%d\n",Ans);
	return 0;
}
