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
const int M=1805;
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[M];
char a[N][M],b[N][M];
int n,m,tot,top,scc,Ans;
int A[N],B[M],dfn[M],low[M];
int p[M],st[M],vis[M],Can[M],Belong[M];
bool Hungary(int x){
	for(int y=1;y<=m;y++){
		if(a[x][y]=='1'&&!vis[y]){
			vis[y]=1;
			if(!p[y]||Hungary(p[y])){
				p[y]=x;return true;
			}
		}
	}
	return false;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;vis[x]=1;
	for(auto y:G[x]){
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		int k=0,tp=top,c=0;scc++;
		do{
			vis[k=st[top--]]=0;Belong[k]=scc;
			for(auto y:G[k])c|=Can[y];c|=Can[k];
		}while(k!=x);
		for(int i=top+1;i<=tp;i++)Can[st[i]]=c;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;j++)b[i][j]='1';
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)vis[j]=0;
		if(Hungary(i))Ans++;
	}
	if(Ans!=n){
		for(int i=1;i<=n;i++)printf("%s\n",b[i]+1);
		return 0;
	}
	for(int i=1;i<=n;i++)A[i]=++tot;
	for(int i=1;i<=m;i++)B[i]=++tot;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='0')continue;
			if(p[j]==i){
				G[B[j]].push_back(A[i]);
				b[i][j]='0';
			}
			else G[A[i]].push_back(B[j]);
		}
	}
	tot=0;
	for(int i=1;i<=n+m;i++)vis[i]=0;
	for(int i=1;i<=m;i++)Can[B[i]]=(p[i]==0);
	for(int i=1;i<=n+m;i++)if(!dfn[i])Tarjan(i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='0')continue;
			if(Belong[A[i]]==Belong[B[j]]||Can[B[j]])b[i][j]='0';
		}
	}
	for(int i=1;i<=n;i++)printf("%s\n",b[i]+1);
	return 0;
}