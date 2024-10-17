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
const int Mod=1000000007;
const int Inv2=500000004;
const int Inv4=250000002;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
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
int C(int n,int m){
	if(n<m)return 0;
	int ans1=1,ans2=1;
	for(int i=m+1;i<=n;i++)ans1=1ll*ans1*i%Mod;
	for(int i=1;i<=n-m;i++)ans2=1ll*ans2*i%Mod;
	return 1ll*ans1*Pow(ans2,Mod-2)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int t=read(),p=abs(read());
	if(t<p){printf("0");return 0;}
	printf("%lld",1ll*C(t*2,t-p)*Pow(Inv4,t)%Mod);
	return 0;
}