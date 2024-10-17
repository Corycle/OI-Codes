#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,q,tot,top,cnt1=1,cnt2=1;
int p[N][M],g[N][M],st[N],f1[N],f2[N],flag[N];
int V[N],dep[N],dfn[N],low[N],h1[N],h2[N];
struct edge{int to,next,data;}e1[N],e2[N];
void Add1(int x,int y,int z){e1[++cnt1]=(edge){y,h1[x],z};h1[x]=cnt1;}
void Add2(int x,int y,int z){e2[++cnt2]=(edge){y,h2[x],z};h2[x]=cnt2;}
void Tarjan(int x,int pre){
	dfn[x]=low[x]=++tot;
	for(int i=h1[x];i;i=e1[i].next){
		int y=e1[i].to;
		if(i==(pre^1))continue;
		if(!dfn[y]){
			st[++top]=i;Tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]){//树边 
				top--;
				Add2(x,y,e1[i].data);
				Add2(y,x,e1[i].data);
			}
			if(dfn[x]==low[y]){//回来了是个环 
				int sum=0,num=0;
				while(1){
					int j=st[top--];
					sum+=e1[j].data;
					f1[e1[j^1].to]=sum;
					V[++num]=e1[j^1].to;
					if(e1[j^1].to==x&&e1[j].to==y)break;
				}
				flag[++n]=1;
				for(int j=1;j<=num;j++){
					int fx=V[j];f2[fx]=sum-f1[fx];
					Add2(n,fx,min(f1[fx],f2[fx]));
					Add2(fx,n,min(f1[fx],f2[fx]));
				}
			}
		}
		else if(dfn[x]>dfn[y]){
			st[++top]=i;
			low[x]=min(low[x],dfn[y]);
		}
	}
}
void DFS(int x,int depth){
	dep[x]=depth;
	for(int i=h2[x];i;i=e2[i].next){
		int y=e2[i].to,w=e2[i].data;
		if(y==p[x][0])continue;
		p[y][0]=x;g[y][0]=w;
		DFS(y,depth+1);
	}
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=g[p[i][j-1]][j-1]+g[i][j-1];
			}
		}
	}
}
int Dist(int x,int y){
	if(x==y)return 0;
	if(dep[x]<dep[y])swap(x,y);int ans=0;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[p[x][k]]>=dep[y]){
			ans+=g[x][k];x=p[x][k];
		}
	}
	if(x==y)return ans;
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){
			ans+=g[x][k]+g[y][k];
			x=p[x][k];y=p[y][k];
		}
	}
	if(flag[p[x][0]]){
		ans+=min(min(f1[x]+f2[y],f2[x]+f1[y]),abs(f1[x]-f1[y]));
	}
	else ans+=g[x][0]+g[y][0];
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add1(x,y,z);Add1(y,x,z);
	}
	Tarjan(1,0);DFS(1,1);ST();
	while(q--)printf("%d\n",Dist(read(),read()));
	return 0;
}