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
const int Mod=998244353;
const int M=805;
const int N=405;
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
vector<int>G[M];
int n,m,cnt,tot,top,scc,Ans;
int h[N],st[N],t[M][M],f[N][N],tmp[N][N];
int dfn[N],low[N],C[N][N],Inv[N],InvC[N][N];
struct edge{int to,next;}d[M];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Addedge(int x,int y){
	G[x].push_back(y);
	G[y].push_back(x);
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
void Prepare(){
	C[0][0]=InvC[0][0]=Inv[0]=Inv[1]=1;
	for(int i=2;i<=n;i++)Inv[i]=1ll*Inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=1;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		for(int j=0;j<=i;j++)InvC[i][j]=Pow(C[i][j],Mod-2);
	}
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;st[++top]=x;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]==low[y]){
				int k=0;scc++;
				do{
					k=st[top--];
					Addedge(scc,k);
					t[scc][k]=++t[scc][0];
				}while(k!=y);
				Addedge(scc,x);
				t[scc][x]=++t[scc][0];
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
void Solve(int x,int fa,int num){
	if(x<=n){
		for(int i=0;i<=num;i++){
			Ans=(Ans+1ll*f[x][i]*InvC[num+1][i]%Mod*Inv[num-i+1]%Mod)%Mod;
		}
		for(auto y:G[x])if(y!=fa)Solve(y,x,num);
	}
	else{
		int sum=t[x][0];
		memcpy(tmp[1],f[fa],sizeof(tmp[1]));
		for(int i=2;i<=sum;i++){
			memset(tmp[i],0,sizeof(tmp[i]));
			for(int j=0;j<=num+i;j++){
				tmp[i][j]=tmp[i-1][j];
				if(j)tmp[i][j]=(tmp[i][j]+tmp[i-1][j-1])%Mod;
			}
		}
		for(auto y:G[x]){
			if(y==fa)continue;
			int dis=abs(t[x][fa]-t[x][y]);
			for(int i=0;i<=num+sum-1;i++){
				f[y][i]=((tmp[dis][i]+tmp[sum-dis][i]-f[fa][i])%Mod+Mod)%Mod;
			}
		}
		for(auto y:G[x])if(y!=fa)Solve(y,x,num+sum-1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	scc=n;Tarjan(1);
	for(int i=1;i<=n;i++){
		memset(f,0,sizeof(f));
		f[i][0]=1;Solve(i,0,0);
	}
	printf("%d",Ans);
	return 0;
}