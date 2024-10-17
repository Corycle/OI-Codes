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
const int N=4e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char Ans[N];
vector<int>G[N];
int n,m,Q,a[N],b[N],c[N],lst[N],pos[N],p[N][M];
int Ask(int l,int r){int k=(int)(log(r-l+1)/log(2));return max(p[l][k],p[r-(1<<k)+1][k]);}
void DFS(int x,int depth){c[depth]=x;if(depth>=n)p[x][0]=c[depth-n+1];for(auto y:G[x])DFS(y,depth+1);}
void Prepare(){for(int j=1;j<M;j++)for(int i=1;i+(1<<j)-1<=m;i++)p[i][j]=max(p[i][j-1],p[i+(1<<(j-1))][j-1]);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){a[i]=read();a[i+n]=a[i];pos[a[i]]=i+n;}
	for(int i=1;i<=m;i++){b[i]=read();G[lst[a[pos[b[i]]-1]]].push_back(i);lst[b[i]]=i;}
	DFS(0,0);Prepare();
	for(int i=1;i<=Q;i++){int l=read(),r=read();Ans[i]=(Ask(l,r)>=l)+'0';}
	printf("%s",Ans+1);
	return 0;
}
