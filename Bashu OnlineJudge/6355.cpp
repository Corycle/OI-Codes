/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=3005;
const int M=205;
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
int n,m,K,Ans;
int a[N],b[N],p[N],vis[N];
int f[N][N],G[N][N],sum1[N][N],sum2[N];
int mod(int x){return x>=Mod?x-Mod:x;}
/*
	O(n^4):
	for(int i=1;i<=n;i++){
		if(!vis[i])continue;
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				f[i][j]=1;
				for(int x=1;x<i;x++){
					if(!vis[x])continue;
					for(int y=1;y<j;y++){
						if(a[x]==b[y]&&G[a[x]][a[i]]){
							f[i][j]=mod(f[i][j]+f[x][y]);
						}
					}
				}
				Ans=mod(Ans+f[i][j]);
			}
		}
	}
	
	O(n^3):
	for(int i=1;i<=n;i++){
		if(!vis[i])continue;
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				f[i][j]=1;
				for(int x=1;x<i;x++){
					if(!vis[x])continue;
					if(G[a[x]][a[i]]){
						f[i][j]=mod(f[i][j]+sum[x][j-1]);
					}
				}
				Ans=mod(Ans+f[i][j]);
			}
			sum[i][j]=mod(sum[i][j-1]+f[i][j]);
		}
	}
	
	O(n^2):
	for(int i=1;i<=n;i++){
		if(!vis[i])continue;
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				f[i][j]=mod(1+sum2[j]);
				Ans=mod(Ans+f[i][j]);
			}
			sum1[i][j]=mod(sum1[i][j-1]+f[i][j]);
			if(G[a[i]][b[j]])sum2[j]=mod(sum2[j]+sum1[i][j-1]);
		}
	}
*/
void Solve(){
	for(int i=1;i<=n;i++){
		if(!vis[i])continue;
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				f[i][j]=mod(1+sum2[j]);
				Ans=mod(Ans+f[i][j]);
			}
			sum1[i][j]=mod(sum1[i][j-1]+f[i][j]);
			if(G[a[i]][b[j]])sum2[j]=mod(sum2[j]+sum1[i][j-1]);
		}
	}
}
int main(){
//	freopen("gu.in","r",stdin);
//	freopen("gu.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++){a[i]=read();}
	for(int i=1;i<=m;i++){b[i]=read();p[++p[0]]=b[i];}
	sort(p+1,p+p[0]+1);p[0]=unique(p+1,p+p[0]+1)-p-1;
	for(int i=1;i<=n;i++){
		int pos=lower_bound(p+1,p+p[0]+1,a[i])-p;
		if(a[i]==p[pos]){vis[i]=1;a[i]=pos;}
	}
	for(int i=1;i<=m;i++)b[i]=lower_bound(p+1,p+p[0]+1,b[i])-p;
	for(int i=1;i<=K;i++){
		int x=read(),y=read();
		int fx=lower_bound(p+1,p+p[0]+1,x)-p;
		int fy=lower_bound(p+1,p+p[0]+1,y)-p;
		if(x==p[fx]&&y==p[fy])G[fx][fy]=1;
	}
	Solve();
	printf("%d",Ans);
	return 0;
}