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
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,T;
int pos[N],sum[N],nxt[N],p[N][M];
struct Node{int l,r,d;}P[N],Q[N];
vector<Node>G[N];
struct Heap{
	priority_queue<int>q1,q2;
	void Insert(int x){q1.push(x);}
	void Delete(int x){q2.push(x);}
	int Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.top();
	}
}F;
void ST(){
	for(int i=1;i<=n;i++)if(nxt[i])p[i][0]=nxt[i]+1;
	for(int j=1;j<M;j++){
		for(int i=1;i<=n;i++)p[i][j]=p[p[i][j-1]][j-1];
	}
}
int Query(int l,int r){
	int ans=0,Pos=l;
	for(int i=M-1;i>=0;i--)if(p[Pos][i]<=r&&p[Pos][i]){Pos=p[Pos][i];ans+=(1<<i);}
	if(!nxt[Pos])return -1;
	if(Pos<=r){ans++;Pos=nxt[Pos]+1;}
	return ans;
}
int main(){
//	freopen("trip.in","r",stdin);
//	freopen("trip.out","w",stdout);
	n=read()-1;m=read();K=read();
	for(int i=1;i<=m;i++){P[i].l=read();P[i].r=read()-1;P[i].d=read();}
	T=read();
	for(int i=1;i<=T;i++){Q[i].l=read();Q[i].r=read()-1;Q[i].d=i;}
	for(int i=1;i<=K;i++){pos[i]=n;F.Insert(pos[i]);}
	F.Insert(0);
	for(int i=1;i<=m;i++){
		G[P[i].r].push_back((Node){P[i].d,0,1});
		G[P[i].l-1].push_back((Node){P[i].d,0,-1});
	}
	for(int i=n;i>=1;i--){
		int num=G[i].size();
		for(int j=0;j<num;j++){
			if(G[i][j].d==1){sum[G[i][j].l]++;if(sum[G[i][j].l]==1)F.Delete(pos[G[i][j].l]);}
			if(G[i][j].d==-1){sum[G[i][j].l]--;if(sum[G[i][j].l]==0)F.Insert(pos[G[i][j].l]=i);}
		}
		nxt[i]=F.Top();
	}
	ST();
	for(int i=1;i<=T;i++)printf("%d\n",Query(Q[i].l,Q[i].r));
	return 0;
}