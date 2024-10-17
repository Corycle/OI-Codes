#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
int n,m,cnt=0;
int f[3005][3005],p[3005],h[3005];
//	设f[rt][j]表示以 rt为根的子树，满足 j个客户取得最大价值
//	只要f[rt][j]>0即为有解 
struct edge{
	int to,data,next;
}d[3005];
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c<='9'&&c>='0'){s=s*10+c-'0';c=getchar();}
	return s;
}
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].data=z;
	d[cnt].next=h[x];
	h[x]=cnt;
}
int hqq_dfs(int rt){
	//	函数的返回值sum为以rt为根节点的子树中叶子结点个数 
	int i,j,k;
	int t[3005];
	memset(t,0,sizeof(t));
	if(rt>n-m){
		f[rt][1]=p[rt];
		return 1;
	}
	int sum=0;
	for(i=h[rt];i;i=d[i].next){
		int l=d[i].to;
		int tk=hqq_dfs(l);
		/*
			sum->当前rt为根的子树下的叶子结点数 (不含l为根的子树下的叶子结点数) 
			tk->当前l为根的子树下的叶子结点数
			//区间dp得最优解 
		*/
		for(j=0;j<=sum;j++)t[j]=f[rt][j];
		for(j=0;j<=sum;j++){
			for(int k=0;k<=tk;k++){
				f[rt][j+k]=max(f[rt][j+k],t[j]+f[l][k]-d[i].data);
			}
		}
		sum+=tk;
	}
	return sum;
}
int main(){
	int i,j,k;
	n=read(),m=read();
	for(i=1;i<=n-m;i++){
		k=read();
		for(j=1;j<=k;j++){
			int x=read(),y=read();
			hqq_add(i,x,y);
		}
	}
	for(i=n-m+1;i<=n;i++)p[i]=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			f[i][j]=-0xfffff;
		}
	}
	hqq_dfs(1);
	for(i=m;i>0;i--){
		if(f[1][i]>=0){
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}