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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],fa[N],son[N],sum[N],num[N],Ans[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x){
	sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS1(y);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
	if(!son[x])return;
	if(num[son[x]]+1<=sum[x]-sum[son[x]]-1)num[x]=(sum[x]-1)%2;
	else num[x]=num[son[x]]+1-(sum[x]-sum[son[x]]-1);
}
void DFS2(int x,int pre,int tot){
	int son2=0;
	if(x!=1){
		int Max=sum[son[x]]>sum[pre]?son[x]:pre;
		if(num[Max]+1<=tot-sum[Max]-1)Ans[x]=(tot-1)%2;
		else Ans[x]=num[Max]+1-(tot-sum[Max]-1);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x]||y==son[x])continue;
		if(sum[y]>sum[son2])son2=y;
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to,tmp=0;
		if(y==fa[x])continue;
		if(y==son[x])tmp=sum[son2]>sum[pre]?son2:pre;
		else tmp=sum[son[x]]>sum[pre]?son[x]:pre;
		DFS2(y,tmp,tot-1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int W=read(),T=read();
	while(T--){
		cnt=0;
		memset(h,0,sizeof(h));
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(num,0,sizeof(num));
		memset(sum,0,sizeof(sum));
		n=read();
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			Add(x,y);Add(y,x);
		}
		DFS1(1);
		DFS2(1,0,n);
		Ans[1]=num[1];
		if(W==3)printf("%d\n",!Ans[1]);
		else{
			for(int i=1;i<=n;i++){
				printf("%d",!Ans[i]?1:0);
			}
			printf("\n");
		}
	}
	return 0;
}