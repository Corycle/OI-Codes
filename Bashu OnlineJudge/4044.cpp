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
const int N=10000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int Mod,f[N];
int Pow(int x,int y,int mod){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%mod;
		tot=1ll*tot*tot%mod;
		y>>=1;
	}
	return ans;
}
int Phi(int x){
	int phi=x;
	for(int i=2;1ll*i*i<=x;i++){
		if(x%i==0){
			phi=phi/i*(i-1);
			while(x%i==0)x/=i;
		}
	}
	if(x!=1)phi=phi/x*(x-1);
	return phi;
}
int F(int p){
	if(p==1)return 0;
	if(f[p])return f[p];
	int phi=Phi(p);
	return f[p]=Pow(2,F(phi)+phi,p);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		Mod=read();
		printf("%d\n",F(Mod));
	}
	return 0;
}