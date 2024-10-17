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
const int Mod=989381;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
map<int,int>vis[N];
int fa[N],sum[N],num[N],Fac[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
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
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		if(vis[x][y])continue;
		vis[x][y]=vis[y][x]=1;
		num[x]++;num[y]++;
		if(num[x]>2){printf("0");return 0;}
		if(num[y]>2){printf("0");return 0;}
		x=Find(x);y=Find(y);
		if(x==y){printf("0");return 0;}
		fa[x]=y;sum[y]+=sum[x];
	}
	int ans1=0,ans2=0;Fac[0]=1;
	for(int i=1;i<=n;i++){
		Fac[i]=1ll*Fac[i-1]*i%Mod;
		if(i==fa[i]){
			if(sum[i]==1)ans1++;
			else ans2++;
		}
	}
	printf("%lld",1ll*Pow(2,ans2)*Fac[ans1+ans2]%Mod);
	return 0;
}