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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,sum,Ans,a[N],f[N];
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
	n=read();sum=1;
	for(int i=1;i<=n;i++){
		a[i]=read();m+=a[i];
		sum=1ll*sum*a[i]%Mod;
	}
	sum=Pow(sum,Mod-2);
	for(int i=1;i<=m;i++)sum=1ll*sum*i%Mod;
	for(int lst=1;lst<=n;lst++){
		int Sum=1ll*sum*a[lst]%Mod;
		for(int i=0;i<=m;i++)f[i]=0;
		f[0]=1;//f[i]表示选出若干种颜色的球恰好有i个球的方案数 
		for(int i=1;i<=n;i++){
			if(i==lst)continue;
			for(int j=m;j>=a[i];j--){
				f[j]=(f[j]-f[j-a[i]]+Mod)%Mod;
			}
		}
		for(int i=0;i<=m;i++){
			Ans=(Ans+1ll*f[i]*Sum%Mod*a[lst]%Mod*Pow(i+a[lst],Mod-2)%Mod)%Mod;
		}
		//枚举有多少个其他颜色的球在pos后面 
	}
	printf("%d",Ans);
	return 0;
}