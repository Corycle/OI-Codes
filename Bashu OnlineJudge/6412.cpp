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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int h[N],a[N],fa[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
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
struct Node{
	int n,f[N];
	void Prepare(int k){n=k;f[k]=1;}
	void Init(){n=0;memset(f,0,sizeof(f));}
	void Inverse(){for(int i=0;i<=n;i++)f[i]=Mod-f[i];}
	friend Node operator+(Node A,Node B){
		A.n=max(A.n,B.n);
		for(int i=0;i<=A.n;i++)A.f[i]=(A.f[i]+B.f[i])%Mod;
		return A;
	}
	friend Node operator-(Node A,Node B){
		A.n=max(A.n,B.n);
		for(int i=0;i<=A.n;i++)A.f[i]=(A.f[i]-B.f[i]+Mod)%Mod;
		return A;
	}
	friend Node operator*(Node A,Node B){
		Node C;C.Init();C.n=A.n+B.n;
		for(int i=0;i<=A.n;i++){
			for(int j=0;j<=B.n;j++){
				C.f[i+j]=(C.f[i+j]+1ll*A.f[i]*B.f[j]%Mod)%Mod;
			}
		}
		return C;
	}
}F[N][3],E;
void DFS(int x){
	F[x][0].Prepare(0);
	F[x][1].Prepare(0);
	F[x][2].Prepare(0);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		F[x][0]=F[x][0]*(F[y][0]+F[y][1]);
		F[x][1]=F[x][1]*(F[y][0]+F[y][1]+F[y][2]);
		F[x][2]=F[x][2]*(F[y][0]*E+F[y][1]+F[y][2]);
	}
	F[x][1]=F[x][1]-F[x][0];
	F[x][1]=F[x][1]*E;
	F[x][2]=F[x][2]*E;
	F[x][2].Inverse();
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	int Ans=0;
	E.Prepare(1);DFS(1);
	F[1][0].Inverse();
	F[1][1].Inverse();
	F[1][2].Inverse();
	for(int i=1;i<=n;i++){
		a[i]=(a[i]+F[1][0].f[i])%Mod;
		a[i]=(a[i]+F[1][1].f[i])%Mod;
		a[i]=(a[i]+F[1][2].f[i])%Mod;
		Ans=(Ans+1ll*n*Pow(i,Mod-2)%Mod*a[i]%Mod)%Mod;
	}
	printf("%d",Ans);
	return 0;
}