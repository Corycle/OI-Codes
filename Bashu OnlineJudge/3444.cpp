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
const int N=1000005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
char s[M][M];
int dx[3]={0,0,1};
int dy[3]={1,-1,0};
int f[N],fa[N],vis[N];
int id(int x,int y){return (x-1)*m+y;}
int mod(int x){return x>=Mod?x-Mod:x;}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Union(int x,int y){
	x=Find(x);y=Find(y);
	if(x!=y){fa[y]=x;f[x]=1ll*f[x]*f[y]%Mod;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n*m;i++){fa[i]=i;f[i]=1;}
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	for(int i=n-1;i>=2;i--){
		for(int j=2;j<=m-1;j++){
			if(s[i][j]=='#')continue;
			for(int k=0;k<3;k++){
				int x=i+dx[k],y=j+dy[k];
				if(s[x][y]=='.')Union(id(i,j),id(x,y));
			}
		}
		for(int j=2;j<=m-1;j++){
			if(s[i][j]=='#')continue;
			int x=Find(id(i,j));
			if(!vis[x]){
				vis[x]=1;
				f[x]=mod(f[x]+1);
			}
		}
		for(int j=2;j<=m-1;j++){
			if(s[i][j]=='#')continue;
			int x=Find(id(i,j));
			vis[x]=0;
		}
	}
	Ans=1;
	for(int i=n-1;i>=2;i--){
		for(int j=2;j<=m-1;j++){
			if(s[i][j]=='#')continue;
			if(fa[id(i,j)]==id(i,j)){
				Ans=1ll*Ans*f[id(i,j)]%Mod;
			}
		}
	}
	printf("%d",Ans);
	return 0;
}