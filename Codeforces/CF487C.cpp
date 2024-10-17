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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
int Phi(int x){
	int phi=x;
	for(int i=2;i*i<=x;i++)if(x%i==0){phi=phi/i*(i-1);while(x%i==0)x/=i;}
	if(x!=1)phi=phi/x*(x-1);
	return phi;
}
int Pow(int x,int y,int mod){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%mod;x=1ll*x*x%mod;y>>=1;}
	return ans;
}
int main(){
//	freopen("perm.in","r",stdin);
//	freopen("perm.out","w",stdout);
	n=read();
	if(!(n&1)&&n>=6){cout<<"NO"<<'\n';return 0;}
	if(n==1)a[1]=1;
	else if(n==2){a[1]=1;a[2]=2;}
	else if(n==4){a[1]=1;a[2]=3;a[3]=2;a[4]=4;}
	else{
		int phi=Phi(n);a[1]=1;a[n]=n;
		if(phi!=n-1){cout<<"NO"<<'\n';return 0;}
		for(int i=2;i<n;i++)a[i]=1ll*i*Pow(i-1,phi-1,n)%n;
	}
	cout<<"YES"<<'\n';
	for(int i=1;i<=n;i++)cout<<a[i]<<'\n';
	return 0;
}
