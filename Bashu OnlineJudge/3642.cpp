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
const int Inv2=499122177;
const int Mod=998244353;
const int M=4100;
const int N=75;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,w,maxn;
int a[N][N],f[N][N][M],Ans[M];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void FWT(int a[],int f){
	for(int i=1,t=0;i<maxn;i<<=1,t++){
		for(int j=0;j<maxn;j++){
			if(i&j){
				if(s[t]=='|')a[j]=(a[j]+f*a[j-i])%Mod;
				if(s[t]=='&')a[j-i]=(a[j-i]+f*a[j])%Mod;
				if(s[t]=='^'){
					int x=a[j-i],y=a[j];
					a[j-i]=mod(x+y);
					a[j]=mod(x-y+Mod);
					if(f==-1){
						a[j]=1ll*a[j]*Inv2%Mod;
						a[j-i]=1ll*a[j-i]*Inv2%Mod;
					}
				}
			}
		}
	}
}
int Kirchhoff(int n){
	int ans=1;
	for(int i=1;i<n;i++){
		int t=i;
		for(int j=i;j<n;j++)if(a[i][j]){t=j;break;}
		if(i!=t){swap(a[i],a[t]);ans=Mod-ans;}
		if(!a[i][i])return 0;
		int inv=Pow(a[i][i],Mod-2);
		for(int j=i+1;j<n;j++){
			if(!a[j][i])continue;
			int dlt=1ll*a[j][i]*inv%Mod;
			for(int k=i;k<n;k++){
				a[j][k]=mod(a[j][k]-1ll*dlt*a[i][k]%Mod+Mod);
			}
		}
		ans=1ll*ans*a[i][i]%Mod;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s",s);
	w=strlen(s);maxn=1<<w;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		f[x][y][z]=mod(f[x][y][z]-1+Mod);
		f[y][x][z]=mod(f[y][x][z]-1+Mod);
		f[x][x][z]++;f[y][y][z]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			FWT(f[i][j],1);
			for(int k=0;k<maxn;k++){
				f[j][i][k]=f[i][j][k];
			}
		}
	}
	for(int k=0;k<maxn;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=f[i][j][k];
			}
		}
		Ans[k]=Kirchhoff(n);
	}
	FWT(Ans,-1);
	for(int i=maxn-1;i>=0;i--){
		if(Ans[i]){printf("%d",i);return 0;}
	}
	printf("-1");
	return 0;
}