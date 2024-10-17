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
const int Mod=59393;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],f[N],F[N],pre[N],deg[N],vis[N];
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
	n=read();m=read();
	for(int i=0;i<=m;i++)a[i]=read();
	for(int x=0;x<=n;x++){
		for(int i=0;i<=m;i++){
			f[x]=(f[x]+1ll*Pow(x,i)*a[i]%Mod)%Mod;
		}
	}
	if(n==1){printf("0 %d\n",f[0]);return 0;}
	for(int i=1;i<=n-2;i++){
		for(int j=0;j<i;j++){
			if(F[i]<F[j]+f[i-j+1]-f[1]){
				F[i]=F[j]+f[i-j+1]-f[1];
				pre[i]=j;
			}
		}
	}
	printf("%d %d\n",n-1,F[n-2]+n*f[1]);
	int sum=n-2,tot=0;
	while(sum){
		deg[++tot]=sum-pre[sum];
		sum=pre[sum];
	}
	vis[1]=1;
	for(int i=1;i<=n;i++)deg[i]++;
	for(int x=1;x<=n;x++){
		if(!vis[x])continue;
		for(int y=1;y<=n;y++){
			if(x==y||vis[y])continue;
			if(!deg[x]||!deg[y])continue;
			vis[x]=vis[y]=1;
			deg[x]--;deg[y]--;
			printf("%d %d\n",x,y);
		}
	}
	return 0;
}