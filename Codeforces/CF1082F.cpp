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
const int N=505;
const int M=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Sum,f[N][N][M],tmp[N][M];
struct Tree{
	int tot=1,ch[N][M],fa[N][N],sum[N],num[N],val[N];
	void Insert(int v){
		int len=strlen(s+1),p=1;
		for(int i=1;i<=len;i++){
			int x=s[i]-'0';
			if(!ch[p][x])ch[p][x]=++tot;
			p=ch[p][x];
		}
		val[p]+=v;Sum+=v*len;
	}
	void DFS(int x,int depth){
		sum[x]=1;fa[x][0]=x;f[x][0][1]=depth*val[x];
		for(int i=1;i<=num[x];i++)f[x][i][0]=(depth-i)*val[x];
		for(int t=0;t<=9;t++){
			int y=ch[x][t];if(!y)continue;
			for(int i=0;i<=num[x];i++)fa[y][++num[y]]=fa[x][i];
			DFS(y,depth+1);
			for(int i=0;i<=num[x];i++)for(int j=0;j<=sum[x]+sum[y]&&j<=m;j++)tmp[i][j]=-inf;
			for(int i=0;i<=num[x];i++){
				for(int j=0;j<=sum[x]&&j<=m;j++){
					for(int k=0;k<=sum[y]&&j+k<=m;k++){
						tmp[i][j+k]=max(tmp[i][j+k],f[x][i][j]+max(f[y][i+1][k],f[y][0][k]));
					}
				}
			}
			for(int i=0;i<=num[x];i++)for(int j=0;j<=sum[x]+sum[y]&&j<=m;j++)f[x][i][j]=tmp[i][j];
			sum[x]+=sum[y];
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read()+1;
	for(int i=1;i<=n;i++){scanf("%s",s+1);tree.Insert(read());}
	int Ans=0;memset(f,-0x3f,sizeof(f));tree.DFS(1,0);
	for(int i=0;i<=m;i++)Ans=max(Ans,f[1][0][i]);
	printf("%d\n",Sum-Ans);
	return 0;
}
