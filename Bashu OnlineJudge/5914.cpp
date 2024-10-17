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
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,root;
int h[N],fa[N],Min[N],dep[N],pos[N],dfn[N],vis[N],p[N][M];
bool cmp(int x,int y){return Min[x]<Min[y];}
priority_queue<int,vector<int>,greater<int> >q;
void DFS1(int x,int depth){
	dep[x]=depth;Min[x]=x;
	for(auto y:G[x]){
		DFS1(y,depth+1);
		Min[x]=min(Min[x],Min[y]);
	}
	sort(G[x].begin(),G[x].end(),cmp);
}
void DFS2(int x){
	for(auto y:G[x])DFS2(y);
	pos[dfn[x]=++tot]=x;
}
void ST(){
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
		}
	}
}
int Insert(int num){
	int ans=0;
	for(int i=1;i<=num;i++){
		int x=pos[q.top()];q.pop();
		vis[x]=1;if(i==num)ans=x;
	}
	return ans;
}
int Delete(int x){
	int ans=dep[x];
	for(int k=(int)(log(n)/log(2));k>=0;k--){
		if(vis[p[x][k]])x=p[x][k];
	}
	vis[x]=0;q.push(dfn[x]);
	return ans-dep[x];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		q.push(i);
		fa[i]=read();
		if(!fa[i])root=i;
		else G[fa[i]].push_back(i);
	}
	DFS1(root,1);DFS2(root);ST();
	while(m--){
		int op=read(),num=read();
		if(op==1)printf("%d\n",Insert(num));
		if(op==2)printf("%d\n",Delete(num));
	}
	return 0;
}