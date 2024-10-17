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
const int Mod=998244353;
const int M=2e7+5;
const int N=2e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,l,r,Ans;
int a[N],b[N],c[N],d[N],Fac[M];
int Pow(int x,int y){
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
	int T=read();Fac[0]=1;
	for(int i=1;i<M;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	while(T--){
		n=read();m=read();l=read();r=read();
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+n+1);
		int tot1=0,tot2=0,t=m;Ans=1;
		for(int i=1,j=0;i<=n;i=j+1){
			j=i;
			while(j<n&&a[i]==a[j+1])j++;
			if(l<=a[i]&&a[i]<=r)b[++tot1]=j-i+1;
			else Ans=1ll*Ans*Fac[j-i+1]%Mod;
		}
		sort(b+1,b+tot1+1);
		tot2++;c[tot2]=0;d[tot2]=r-l+1-tot1;
		for(int i=1,j=0;i<=tot1;i=j+1){
			j=i;
			while(j<tot1&&b[i]==b[j+1])j++;
			tot2++;c[tot2]=b[i];d[tot2]=j-i+1;
		}
		c[tot2+1]=inf;d[tot2+1]=1;
		for(int i=1;i<=tot2;i++){
			ll dlt=1ll*(c[i+1]-c[i])*d[i];
			if(dlt<=t){t-=dlt;d[i+1]+=d[i];}
			else{
				int x=t/d[i],y=t%d[i];
				Ans=1ll*Ans*Pow(Fac[c[i]+x+1],y)%Mod;
				Ans=1ll*Ans*Pow(Fac[c[i]+x],d[i]-y)%Mod;
				for(int j=i+1;j<=tot2;j++){
					Ans=1ll*Ans*Pow(Fac[c[j]],d[j])%Mod;
				}
				break;
			}
		}
		Ans=1ll*Fac[n+m]*Pow(Ans,Mod-2)%Mod;
		printf("%d\n",Ans);
	}
	return 0;
}