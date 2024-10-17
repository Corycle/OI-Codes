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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,h[N],K[N],B[N],deg[N];
struct edge{int to,next,dist;}d[N*2];
void Add(int x,int y,int z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
void DFS(int x,int fa){
	int num=0,SumK=0,SumB=0,SumD=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		SumD=mod(SumD+d[i].dist);
		if(y==fa)continue;
		DFS(y,x);num++;
		SumK=mod(SumK+K[y]);
		SumB=mod(SumB+B[y]);
	}
	if(!num){K[x]=0;return;}
	K[x]=Pow(mod(deg[x]-SumK+Mod),Mod-2);
	B[x]=1ll*mod(SumB+SumD)*Pow(mod(deg[x]-SumK+Mod),Mod-2)%Mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read()+1,y=read()+1,z=read();
		Add(x,y,z);Add(y,x,z);deg[x]++;deg[y]++;
	}
	DFS(1,0);
	printf("%d\n",B[1]);
	return 0;
}
