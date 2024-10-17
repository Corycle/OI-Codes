#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int P=998244353;
const int Mod=1e9+7;
const int N=5000005;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,a[N],pre[N],suc[N],inv[N];
inline int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int sum=1,ans=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum=1ll*sum*a[i]%Mod;
	}
	sum=Pow(sum,Mod-2);
	a[0]=a[n+1]=pre[0]=suc[n+1]=1;
	for(int i=1;i<=n;i++)pre[i]=1ll*pre[i-1]*a[i]%Mod;
	for(int i=n;i>=1;i--)suc[i]=1ll*suc[i+1]*a[i]%Mod;
	int tmp=Pow(P,n),Inv=Pow(P,Mod-2);
	for(int i=1;i<=n;i++){
		inv[i]=1ll*pre[i-1]*suc[i+1]%Mod*sum%Mod;
		tmp=1ll*tmp*Inv%Mod;
		ans=(ans+1ll*inv[i]*tmp%Mod)%Mod;
	}
	printf("%d",ans);
	return 0;
}