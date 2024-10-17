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
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,a[N][N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int Kirchoff(){
	int Ans=1;
	for(int i=2;i<=n;i++){
		int t=0;
		for(int j=i;j<=n;j++)if(a[j][i]){t=i;break;}
		if(t!=i){swap(a[i],a[t]);Ans=Mod-Ans;}
		for(int j=i+1;j<=n;j++){
			int dlt=1ll*a[j][i]*Pow(a[i][i],Mod-2)%Mod;
			for(int k=i;k<=n;k++)a[j][k]=(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod)%Mod;
		}
		Ans=1ll*Ans*a[i][i]%Mod;
	}
	return Ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=n;j++){
			if(s[j]=='1'){
				a[i][j]--;
				a[j][j]++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=(a[i][j]%Mod+Mod)%Mod;
		}
	}
	printf("%d",Kirchoff());
	return 0;
}