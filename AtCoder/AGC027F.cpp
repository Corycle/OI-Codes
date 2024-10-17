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
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,Ans,t[N],deg[N];
struct Graph{
	int fa[N];
	vector<int>G[N];
	void DFS(int x,int Fa){fa[x]=Fa;for(auto y:G[x])if(y!=Fa)DFS(y,x);}
	void Addedge(int x,int y){G[x].push_back(y);G[y].push_back(x);}
	void Clear(){for(int i=1;i<N;i++)G[i].clear();}
}G1,G2;
bool Check(int x){return G1.fa[x]==G2.fa[x];}
void Add(int x,int y){G[x].push_back(y);deg[y]++;}
int Solve(int Root){
	for(int i=1;i<=n;i++){G[i].clear();deg[i]=0;}
	for(int i=1;i<=n;i++)if(Check(i)&&!Check(G1.fa[i]))return inf;
	for(int i=1;i<=n;i++)if(!Check(i)&&!Check(G1.fa[i]))Add(i,G1.fa[i]);
	for(int i=1;i<=n;i++)if(!Check(i)&&!Check(G2.fa[i]))Add(G2.fa[i],i);
	int num=0;queue<int>q;
	for(int i=1;i<=n;i++)if(!Check(i))num++;
	for(int i=1;i<=n;i++)if(!Check(i)&&!deg[i])q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		for(auto y:G[x])if(!(--deg[y]))q.push(y);
	}
	for(int i=1;i<=n;i++)if(deg[i])return inf;
	return num;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		n=read();Ans=inf;
		for(int i=1;i<=n;i++)t[i]=0;G1.Clear();G2.Clear();
		for(int i=1;i<n;i++){int x=read(),y=read();G1.Addedge(x,y);t[x]++;t[y]++;}
		for(int i=1;i<n;i++){int x=read(),y=read();G2.Addedge(x,y);}
		G1.DFS(1,0);G2.DFS(1,0);if(Solve(1)==0){puts("0");continue;}
		for(int x=1;x<=n;x++)if(t[x]==1){
			G2.DFS(x,0);
			for(int y=1;y<=n;y++)if(x!=y){
				G1.DFS(y,0);G1.fa[y]=x;G1.fa[x]=0;
				Ans=min(Ans,Solve(x)+1);
			}
		}
		printf("%d\n",Ans!=inf?Ans:-1);
	}
	return 0;
}
