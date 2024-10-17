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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,sum,Inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	Inv[0]=Inv[1]=1;
	for(int i=2;i<=m;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=m;i++)Inv[i]=1ll*Inv[i]*Inv[i-1]%Mod;
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int S2(int n,int m){
	int ans=0;
	for(int k=0;k<=m;k++){
		int t=(k&1?Mod-1:1);
		ans=mod(ans+1ll*t*Pow(m-k,n)%Mod*Inv[k]%Mod*Inv[m-k]%Mod);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++)sum=mod(sum+read());
	printf("%lld",1ll*sum*mod(S2(n,m)+1ll*(n-1)*S2(n-1,m)%Mod)%Mod);
	return 0;
}
