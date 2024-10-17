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
const int N=18;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int a[N][N],num[N];
struct edge{int s,t;}e[N][N*N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
int Kirchhoff(){
	int ans=1;
	for(int i=1;i<n;i++){
		int t=i,Max=a[i][i];
		for(int j=i+1;j<n;j++){
			if(a[j][i]>Max){Max=a[j][i];t=j;}
		}
		if(t!=i){swap(a[i],a[t]);ans=(Mod-ans)%Mod;}
		for(int j=i+1;j<n;j++){
			int dlt=1ll*a[j][i]*Pow(a[i][i],Mod-2)%Mod;
			for(int k=i;k<n;k++){
				a[j][k]=(a[j][k]-1ll*a[i][k]*dlt%Mod+Mod)%Mod;
			}
		}
		ans=1ll*ans*a[i][i]%Mod;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=n-1;
	for(int i=1;i<=m;i++){
		num[i]=read();
		for(int j=1;j<=num[i];j++){
			e[i][j].s=read();
			e[i][j].t=read();
		}
	}
	int Sta=(1<<m)-1;
	for(int S=1;S<=Sta;S++){
		int tmp=n;
		memset(a,0,sizeof(a));
		for(int i=1;i<=m;i++){
			if((S>>(i-1))&1){
				for(int j=1;j<=num[i];j++){
					int x=e[i][j].s,y=e[i][j].t;
					a[x][x]++;a[y][y]++;
					a[x][y]--;a[y][x]--;
				}
				tmp--;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=(a[i][j]%Mod+Mod)%Mod;
			}
		}
		tmp=(tmp&1)?1:Mod-1;
		Ans=(Ans+1ll*Kirchhoff()*tmp%Mod+Mod)%Mod;
	}
	printf("%d",Ans);
	return 0;
}