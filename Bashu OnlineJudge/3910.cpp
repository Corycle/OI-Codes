#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=152383;//随便找一个数 
const int Mul=5579;//再随便找一个数 
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Xinyue_Shuai{
	//这是一个裸的 KM  
	//xinyue宇宙第一帅 
	int n,lx[N],ly[N],visx[N],visy[N],p[N],w[N][N];
	bool DFS(int x){
		visx[x]=1;
		for(int y=1;y<=n;y++){
			if(!visy[y]&&lx[x]+ly[y]==w[x][y]){
				visy[y]=1;
				if(!p[y]||DFS(p[y])){p[y]=x;return true;}
			}
		}
		return false;
	}
	void Adjust(){
		int d=inf;
		for(int i=1;i<=n;i++){
			if(!visx[i])continue;
			for(int j=1;j<=n;j++){
				if(!visy[j])d=min(d,lx[i]+ly[j]-w[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			if(visx[i])lx[i]-=d;
			if(visy[i])ly[i]+=d;
		}
	}
	int KM(){
		memset(p,0,sizeof(p));
		for(int i=1;i<=n;i++){
			lx[i]=-inf;ly[i]=0;
			for(int j=1;j<=n;j++){
				w[i][j]*=-1;
				//求的是最小更改次数 
				//所以我们将所有边取反 
				lx[i]=max(lx[i],w[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			while(1){
				memset(visx,0,sizeof(visx));
				memset(visy,0,sizeof(visy));
				if(DFS(i))break;Adjust();
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			if(p[i])ans+=w[p[i]][i];
		}
		return -ans;//注意 
	}
}P;
int n,cnt,root,Ans=inf,tmp=inf;
int h[N],fa[N],s1[N],s2[N],vis[N],sum[N];
int Hash[N],f[N][N],c1[N][N],c2[N][N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){//双向边 
	d[++cnt]=(edge){y,h[x]};h[x]=cnt;
	d[++cnt]=(edge){x,h[y]};h[y]=cnt;
}
bool cmp(int x,int y){
	//以Hash值从小到大排序 
	return Hash[x]<Hash[y];
}
void Find(int x){//求树的重心 
	int Max=0;
	vis[x]=sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Find(y);
		sum[x]+=sum[y];
		Max=max(Max,sum[y]);
	}
	Max=max(Max,n-sum[x]);
	if(Max<tmp){tmp=Max;root=x;}
	//找重心，不说了 
}
void DFS(int x,int prt,int c[][N]){
	fa[x]=prt;Hash[x]=2019;
	memset(c[x],0,sizeof(c[x]));
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		DFS(y,x,c);
		c[x][++c[x][0]]=y;
		//存入每个点的所有孩子，用于DP
	}
	sort(c[x]+1,c[x]+c[x][0]+1,cmp);
	//将x的所有孩子以Hash值排序 
	for(int i=1;i<=c[x][0];i++){
		Hash[x]=((Hash[x]*Mul)^Hash[c[x][i]])%Mod;
		//树的同构 Hash 
	}
}
int DP(int x,int y){
	if(f[x][y]!=-1)return f[x][y];//类似记忆化 
	f[x][y]=s1[x]^s2[y];//x的初始值是否与目标值不同 
	int num=c1[x][0];
	//既然x和y同构，那他们的孩子的Hash值肯定相同 
	for(int i=1;i<=num;i++){
		int j=i;
		while(j<=num&&Hash[c1[x][j+1]]==Hash[c1[x][i]])j++;
		//i-j中的所有子树都同构 
		//方便之后的建边，孩子在DFS中是排过序的 
		for(int k=i;k<=j;k++){
			for(int l=i;l<=j;l++){
				DP(c1[x][k],c2[y][l]);
				//处理x和y的孩子的对应关系 
			}
		}
		//先对孩子处理完再处理本身 
		for(int k=i;k<=j;k++){
			for(int l=i;l<=j;l++){
				int dlt=DP(c1[x][k],c2[y][l]);
				P.w[k-i+1][l-i+1]=dlt;
				//让x的孩子和y的孩子看起来一样所需要的最小代价 
			}
		}
		//初始化边权 
		P.n=j-i+1;
		f[x][y]+=P.KM();
		//KM进行匹配，费用流也可以 
		i=j;
	}
	return f[x][y];
}
int main(){
	n=read();
	for(int i=1;i<n;i++)Add(read(),read());
	for(int i=1;i<=n;i++)s1[i]=read();//这是初始状态 
	for(int i=1;i<=n;i++)s2[i]=read();//这是目标状态 
	Find(1);//先找到重心 root 
	DFS(root,0,c2);
	//以重心为根重新 Hash，每个点的孩子存入 C2 
	tmp=Hash[root];
	for(int i=1;i<=n;i++){
		DFS(i,0,c1);
		//以i为根重新 Hash，每个点的孩子存入 C1 
		if(Hash[i]==tmp){//如果与原树同构 
			memset(f,-1,sizeof(f));
			Ans=min(Ans,DP(i,root));//DP，更新答案 
		}
	}
	printf("%d\n",Ans);
	return 0;
}