/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int Mod=64123;
const int N=1670;
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
int n,K,W,cnt,root;
int a[N],h[N],f[N][N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
inline int MOD(int x){
	return x>Mod?x-Mod:x;
}
void DFS(int x,int fa){
	int type=(a[x]>a[root])||(a[x]==a[root]&&x<root);
	for(int i=1;i<=K;i++){
		f[x][i+type]=MOD(f[x][i+type]+f[fa][i]);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
	}
	for(int i=1;i<=K;i++){
		f[fa][i]=MOD(f[fa][i]+f[x][i]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();W=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	int Ans=0;
	for(int i=1;i<=n;i++){
		int num=0;root=i;
		for(int j=1;j<=n;j++){
			if((a[j]>a[i])||(a[j]==a[i]&&j<i))num++;
		}
		if(num+1<K)continue;
		for(int x=1;x<=n;x++){
			for(int j=0;j<=K;j++){
				f[x][j]=0;
			}
		}
		f[i][1]=1;
		for(int j=h[i];j;j=d[j].next){
			DFS(d[j].to,i);
		}
		Ans=MOD(Ans+1ll*f[i][K]*a[i]%Mod);
	}
	printf("%d",Ans);
	return 0;
}