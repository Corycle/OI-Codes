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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Ans;
int fa[N],F[N],G[N];
struct Node{int x,y,type;}P[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool cmp(Node A,Node B){
	return A.y!=B.y?A.y<B.y:A.type<B.type;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();Ans=tot=0;
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=n;i++)F[i]=G[i]=0;
		for(int i=1;i<n;i++)P[++tot]=(Node){i,read(),-1};
		for(int i=1;i<=m;i++){
			int x=read(),y=read(),type=read();
			P[++tot]=(Node){x,y,type};
		}
		sort(P+1,P+tot+1,cmp);
		for(int i=1;i<=tot;i++){
			if(P[i].type==-1){
				int x=Find(P[i].x),y=Find(P[i].x+1);
				fa[y]=x;G[x]+=G[y];F[x]=max(G[x],F[x]+F[y]);
			}
			if(P[i].type==0){
				F[Find(P[i].x)]++;
			}
			if(P[i].type==1){
				int x=Find(P[i].x);
				G[x]++;F[x]=max(F[x],G[x]);
			}
		}
		for(int i=1;i<=n;i++)Ans=max(Ans,max(F[i],G[i]));
		printf("%d\n",Ans);
	}
	return 0;
}