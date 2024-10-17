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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N],b[N];
int n,cnt1,cnt2,cnt3,Fac[N],Inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	Fac[0]=Fac[1]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[i-1]*Inv[i]%Mod;
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
	return n<m?0:1ll*Fac[n]*Inv[m]%Mod*Inv[n-m]%Mod;
}
int S(int n,int m){
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
	n=read();Prepare();
	scanf("%s%s",a+1,b+1);
	for(int i=1;i<=n;i++){
		if(a[i]=='1'&&b[i]=='0')cnt1++;
		if(a[i]=='0'&&b[i]=='1')cnt2++;
		if(a[i]=='1'&&b[i]=='1')cnt3++;
	}
	if(cnt1<cnt2){puts("0");return 0;}
	int Ans=1;
	Ans=1ll*Ans*Fac[cnt1]%Mod*Fac[cnt2]%Mod*Fac[cnt3]%Mod;
	Ans=1ll*Ans*Pow(n-1,cnt1-cnt2)%Mod*C(cnt1,cnt2)%Mod*S(cnt1+cnt3,cnt1)%Mod;
	printf("%d",Ans);
	return 0;
}