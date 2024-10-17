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
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,num,Ans,Max,a[N],h[N],vis[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void DFS(int x,int fa,int dist){
	if(dist<=Max)num++;else return;
	for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(y==fa||vis[y])continue;DFS(y,x,dist+1);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read()+1;Ans=n;
	for(int i=1;i<n;i++){int x=read(),y=read();Add(x,y);Add(y,x);}
	if(m&1){
		Max=(m-1)/2;
		for(int i=1;i<=n;i++){num=0;DFS(i,0,0);Ans=min(Ans,n-num);}
	}
	else{
		Max=m/2-1;
		for(int x=1;x<=n;x++){
			for(int i=h[x];i;i=d[i].next){
				int y=d[i].to;
				vis[x]=vis[y]=1;
				num=0;DFS(x,0,0);DFS(y,0,0);Ans=min(Ans,n-num);
				vis[x]=vis[y]=0;
			}
		}
	}
	printf("%d\n",Ans);
	return 0;
}
