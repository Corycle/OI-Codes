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
const int Mod=10007;
const int N=255;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int a[N][N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%Mod;
		tot=tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Solve(){
	Ans=1;
	for(int i=2;i<=n;i++){
		int k=i,Max=a[i][i];
		for(int j=i+1;j<=n;j++){
			if(Max<a[j][i]){k=j;Max=a[j][i];}
		}
		if(k!=i){swap(a[i],a[k]);Ans=(Mod-Ans)%Mod;}
		for(int j=i+1;j<=n;j++){
			int dlt=a[j][i]*Pow(a[i][i],Mod-2)%Mod;
			for(int k=i;k<=n;k++){
				a[j][k]=(a[j][k]-a[i][k]*dlt%Mod+Mod)%Mod;
			}
		}
		Ans=Ans*a[i][i]%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int y=read(),x=read();
		a[y][y]++;a[x][y]--;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=(a[i][j]%Mod+Mod)%Mod;
		}
	}
	Solve();
	printf("%d",Ans);
	return 0;
}