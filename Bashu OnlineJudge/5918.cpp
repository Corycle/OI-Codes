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
#include<set>
#define ll long long
#define set_it multiset<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],w[N];
multiset<int>F[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Merge(int x,int y){
	if(F[x].size()<F[y].size())swap(F[x],F[y]);
	for(auto data:F[y])F[x].insert(data);
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS(y);Merge(x,y);
	}
	set_it p=F[x].lower_bound(w[x]);
	if(p!=F[x].end())F[x].erase(p);
	F[x].insert(w[x]);
	Ans=max(Ans,(int)(F[x].size()));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		w[i]=read();
		Add(read(),i);
	}
	DFS(1);
	printf("%d",Ans);
	return 0;
}