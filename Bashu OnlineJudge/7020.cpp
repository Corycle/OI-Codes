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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<int,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<pii>F[N];
int n,m,cnt,Mod;
int a[N],h[N],Ans[N],pans[N],Answer[N];
int f1[N][2],f2[N][2],g1[N][2],g2[N][2];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS1(int x,int fa){
	int Sum0=1,Sum1=1;Ans[x]=0;
	f1[x][0]=f1[x][1]=1;f2[x][0]=f2[x][1]=a[x]%Mod;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS1(y,x);
		Ans[x]=mod(Ans[x]+Ans[y]);
		if(a[y]>a[x]){
			Ans[x]=mod(Ans[x]+mod(1ll*f2[x][0]*f1[y][1]%Mod+1ll*Sum0*f2[y][1]%Mod));
			f2[x][0]=mod(f2[x][0]+mod(f2[y][1]+1ll*f1[y][1]*a[x]%Mod));
			f1[x][0]=mod(f1[x][0]+f1[y][1]);
			Sum0=mod(Sum0+f1[y][1]);
		}
		if(a[y]<a[x]){
			Ans[x]=mod(Ans[x]+mod(1ll*f2[x][1]*f1[y][0]%Mod+1ll*Sum1*f2[y][0]%Mod));
			f2[x][1]=mod(f2[x][1]+mod(f2[y][0]+1ll*f1[y][0]*a[x]%Mod));
			f1[x][1]=mod(f1[x][1]+f1[y][0]);
			Sum1=mod(Sum1+f1[y][0]);
		}
	}
}
void DFS2(int x,int fa){
	if(fa){
		Ans[fa]=pans[x];
		f1[fa][0]=g1[x][0];f1[fa][1]=g1[x][1];
		f2[fa][0]=g2[x][0];f2[fa][1]=g2[x][1];
	}
	int tmp=Ans[x],f10=f1[x][0],f11=f1[x][1],f20=f2[x][0],f21=f2[x][1];
	int Sum0=1,Sum1=1;
	f1[x][0]=f1[x][1]=1;f2[x][0]=f2[x][1]=a[x]%Mod;Ans[x]=0;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		Ans[x]=mod(Ans[x]+Ans[y]);
		if(a[y]>a[x]){
			Ans[x]=mod(Ans[x]+mod(1ll*f2[x][0]*f1[y][1]%Mod+1ll*Sum0*f2[y][1]%Mod));
			f2[x][0]=mod(f2[x][0]+mod(f2[y][1]+1ll*f1[y][1]*a[x]%Mod));
			f1[x][0]=mod(f1[x][0]+f1[y][1]);
			Sum0=mod(Sum0+f1[y][1]);
		}
		if(a[y]<a[x]){
			Ans[x]=mod(Ans[x]+mod(1ll*f2[x][1]*f1[y][0]%Mod+1ll*Sum1*f2[y][0]%Mod));
			f2[x][1]=mod(f2[x][1]+mod(f2[y][0]+1ll*f1[y][0]*a[x]%Mod));
			f1[x][1]=mod(f1[x][1]+f1[y][0]);
			Sum1=mod(Sum1+f1[y][0]);
		}
	}
//	cout<<"DFS2: "<<x<<endl;
//	for(int i=1;i<=n;i++)cout<<Ans[i]<<" ";cout<<endl;
	int num=F[x].size();
	for(int i=0;i<num;i++)Answer[F[x][i].scd]=Ans[F[x][i].fst];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		pans[y]=mod(Ans[x]-Ans[y]+Mod);
		if(a[y]>a[x]){
			int psum=mod(Sum0-f1[y][1]+Mod);
			g1[y][0]=mod(f1[x][0]-f1[y][1]+Mod);
			g2[y][0]=mod(f2[x][0]-mod(f2[y][1]+1ll*f1[y][1]*a[x]%Mod)+Mod);
			pans[y]=mod(pans[y]-mod(1ll*g2[y][0]*f1[y][1]%Mod+1ll*psum*f2[y][1]%Mod)+Mod);
		}
		if(a[y]<a[x]){
			int psum=mod(Sum1-f1[y][0]+Mod);
			g1[y][1]=mod(f1[x][1]-f1[y][0]+Mod);
			g2[y][1]=mod(f2[x][1]-mod(f2[y][0]+1ll*f1[y][0]*a[x]%Mod)+Mod);
			pans[y]=mod(pans[y]-mod(1ll*g2[y][1]*f1[y][0]%Mod+1ll*psum*f2[y][0]%Mod)+Mod);
		}
	}
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==fa)continue;DFS2(y,x);}
	Ans[x]=tmp;f1[x][0]=f10;f1[x][1]=f11;f2[x][0]=f20;f2[x][1]=f21;
}
int main(){
//	freopen("path.in","r",stdin);
//	freopen("path.out","w",stdout);
	n=read();Mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	DFS1(1,0);
	m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();F[x].push_back(mp(y,i));}
	DFS2(1,0);
	for(int i=1;i<=m;i++)printf("%d\n",Answer[i]);
	return 0;
}