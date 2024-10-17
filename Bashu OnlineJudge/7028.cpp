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
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a,b,Mul;
ll lowbit(ll x){return x&(-x);}
ull Pow(ull x,int y){ull ans=1;while(y){if(y&1)ans=ans*x;x=x*x;y>>=1;}return ans;}
int Pow2(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
int Solve(int a,int b){
	if((a-b)&1)return 1;
	if((a&1)&&(b&1))return lowbit((ll)(Pow(a,n)-Pow(b,n)))%Mod;
	return 1ll*Mul*Solve(a/2,b/2)%Mod;
}
int main(){
//	freopen("journey.in","r",stdin);
//	freopen("journey.out","w",stdout);
	int Case=read();
	while(Case--){
		a=read();b=read();n=read();Mul=Pow2(2,n);
		cout<<Solve(a,b)<<'\n';
	}
	return 0;
}