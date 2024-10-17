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
const int M=1e6+5;
const int NM=6e7+5;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,K,tot,tot1,tot2;
int a[N],w[N],fa[N],sum[N],val[N];
int id1[N],id2[N],pos1[N],pos2[N];
int q1[M],q2[M],F1[NM],F2[NM],flag[N];
inline int id(int x,int y){return x*(K+1)+y;}
inline void Solve(int pos[],int f[]){
	for(int i=1;i<=tot;i++){
		int x=pos[i];
		int l=1,r=1;q1[1]=q2[1]=0;
		for(int j=1;j<=K;j++){
			while(l<=r&&q1[l]<j-a[x])l++;
			f[id(i,j)]=max(f[id(i-sum[x],j)],q2[l]+j*w[x]);
			while(l<=r&&q2[r]<=f[id(i-1,j)]-j*w[x])r--;
			r++;q1[r]=j;q2[r]=f[id(i-1,j)]-j*w[x];
		}
	}
}
inline void DFS1(int x){
	sum[x]=1;val[x]=val[fa[x]]+w[x];
	for(auto y:G[x]){DFS1(y);sum[x]+=sum[y];}
	pos1[id1[x]=++tot1]=x;
}
inline void DFS2(int x){
	for(int i=G[x].size()-1;i>=0;i--)DFS2(G[x][i]);
	pos2[id2[x]=++tot2]=x;
}
inline void Clear(){
	int maxn=(tot+1)*(K+1);tot1=tot2=0;
	for(int i=0;i<=tot;i++){G[i].clear();sum[i]=val[i]=flag[i]=0;}
    for(int i=0;i<=maxn;i++){F1[i]=F2[i]=0;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();K=read();tot=n;
		for(int i=1;i<=n;i++){
			fa[i]=read();a[i]=read();w[i]=read();
			G[fa[i]].push_back(i);flag[fa[i]]=1;
			if(a[i]>1){
				G[i].push_back(++tot);
				a[tot]=a[i]-1;w[tot]=w[i];a[i]=1;
			}
		}
		DFS1(1);DFS2(1);
		Solve(pos1,F1);
		Solve(pos2,F2);
		int Ans=0;
		for(int x=1;x<=n;x++){
			if(flag[x])continue;
			for(int i=0;i<=K;i++){
				Ans=max(Ans,val[x]+F1[id(id1[x]-1,i)]+F2[id(id2[x]-sum[x],K-i)]);
			}
		}
		printf("%d\n",Ans);
		Clear();
	}
	return 0;
}