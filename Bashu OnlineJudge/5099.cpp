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
const ll inf=0x3f3f3f3f;
const ll Mod=1e9+7;
const ll M=100005;
const ll N=4005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
ll n,m,sum,Ans,Lim1,Lim2,f[N][N];
int main(){
//	freopen("bracket.in","r",stdin);
//	freopen("bracket.out","w",stdout);
	n=read();m=read();
	scanf("%s",s+1);
	for(ll i=1;i<=m;i++){
		if(s[i]=='(')sum++;
		if(s[i]==')')sum--;
		Lim1=min(Lim1,sum);
	}
	Lim1=abs(Lim1);sum=0;
	for(ll i=m;i>=1;i--){
		if(s[i]=='(')sum++;
		if(s[i]==')')sum--;
		Lim2=max(Lim2,sum);
	}
	n-=m;
	if(Lim1+Lim2>n){
		printf("0");
		return 0;
	}
	f[0][0]=1;
	for(ll i=1;i<=n;i++){
		f[i][0]=f[i-1][1];
		for(ll j=1;j<=n;j++){
			f[i][j]=(f[i][j]+f[i-1][j-1])%Mod;
			f[i][j]=(f[i][j]+f[i-1][j+1])%Mod;
		}
	}
	for(ll i=0;i<=n;i++){
		for(ll j=0;j<=n;j++){
			Ans=(Ans+f[i][Lim1+j]*f[n-i][Lim2+j]%Mod)%Mod;
		}
	}
	printf("%lld",Ans);
	return 0;
}