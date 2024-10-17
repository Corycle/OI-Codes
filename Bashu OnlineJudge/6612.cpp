/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<vector>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<stack>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int N=152505;
const int M=35;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Max,Min;
int vis[N],phi[N],num[N],prime[N],fa[M],Sum[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
int mod(int x){return x>=Mod?x-Mod:x;}
struct Edge{int x,y;};
vector<Edge>E[N];
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
	ll x,y;
	friend Node operator+(Node A,Node B){return (Node){mod(A.x+B.x),mod(A.y+B.y)};}
	friend Node operator-(Node A,Node B){return (Node){mod(A.x-B.x+Mod),mod(A.y-B.y+Mod)};}
	friend Node operator*(Node A,Node B){return (Node){1ll*A.x*B.x%Mod,mod(1ll*A.x*B.y%Mod+1ll*A.y*B.x%Mod)};}
	friend Node operator/(Node A,Node B){int Inv=Pow(B.x,Mod-2);return (Node){1ll*A.x*Inv%Mod,1ll*mod(1ll*A.y*B.x%Mod-1ll*A.x*B.y%Mod+Mod)*Inv%Mod*Inv%Mod};}
}a[M][M];
void Prepare(int maxn){
	phi[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){prime[++cnt]=i;phi[i]=i-1;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j])phi[i*prime[j]]=1ll*phi[i]*phi[prime[j]]%Mod;
			else{phi[i*prime[j]]=1ll*phi[i]*prime[j]%Mod;break;}
		}
	}
}
int Kirchhoff(int n){
	int flag=0;
	Node ans=(Node){1,0};
	for(int i=1;i<n;i++){
		int t=i;
		for(int j=i;j<n;j++)if(a[j][i].x)t=j;
		if(i!=t){swap(a[i],a[t]);flag^=1;}
		if(!a[i][i].x)return 0;
		ans=ans*a[i][i];
		for(int j=i+1;j<n;j++){
			Node dlt=a[j][i]/a[i][i];
			for(int k=i;k<n;k++)a[j][k]=a[j][k]-dlt*a[i][k];
		}
	}
	if(flag)ans.y=mod(Mod-ans.y);
	return ans.y;
}
void Update(int x,int y,Node val){
	a[x][x]=a[x][x]+val;
	a[y][y]=a[y][y]+val;
	a[x][y]=a[x][y]-val;
	a[y][x]=a[y][x]-val;
}
int F(int T){
	int Num=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=T;i<=Max;i+=T){
		for(int j=0;j<num[i];j++){
			int x=E[i][j].x,y=E[i][j].y;
			if(Find(x)!=Find(y)){
				fa[Find(x)]=fa[Find(y)];
				Num++;
			}
		}
	}
	if(Num!=n-1)return 0;
	memset(a,0,sizeof(a));
	for(int i=T;i<=Max;i+=T){
		for(int j=0;j<num[i];j++){
			Update(E[i][j].x,E[i][j].y,(Node){1,i});
		}
	}
	return Kirchhoff(n);
}
int main(){
//	freopen("count.in","r",stdin);
//	freopen("count.out","w",stdout);
	n=read();m=read();Max=0;Min=inf;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		E[z].push_back((Edge){x,y});
		Max=max(Max,z);
		Min=min(Min,z);
		num[z]++;
	}
	for(int i=1;i<=Max;i++){
		for(int j=i;j<=Max;j+=i)Sum[i]+=num[j];
	}
	int Ans=0;
	Prepare(Max);
	for(int T=1;T<=Max;T++){
		if(Sum[T]<n-1)continue;
		Ans=mod(Ans+1ll*F(T)*phi[T]%Mod);
	}
	printf("%d",Ans);
	return 0;
}