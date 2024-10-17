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
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<pii>F[N];
int n,m,a[N],fa[N],Ans[N];
struct Edge{int x,y,w;}E[N];
priority_queue<int,vector<int>,greater<int> >q;
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Update(int x){
	while(F[x].size()&&(*F[x].begin()).fst<=a[x]){
		q.push((*F[x].begin()).scd);F[x].erase(F[x].begin());
	}
}
void Merge(int x,int y){
	if(F[x].size()<F[y].size())swap(x,y);fa[y]=x;a[x]+=a[y];
	while(F[y].size()){F[x].insert(*F[y].begin());F[y].erase(F[y].begin());}
	Update(x);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){a[i]=read()*2;fa[i]=i;}
	for(int i=1;i<=m;i++){
		E[i].x=read();E[i].y=read();E[i].w=read()*2;
		F[E[i].x].insert(mp(E[i].w/2,i));
		F[E[i].y].insert(mp(E[i].w/2,i));
	}
	for(int i=1;i<=n;i++)Update(i);
	while(q.size()){
		int id=q.top();q.pop();
		int x=Find(E[id].x),y=Find(E[id].y);
		if(x==y)continue;
		if(a[x]+a[y]>=E[id].w){Merge(x,y);Ans[++Ans[0]]=id;}
		else{
			ll dlt=E[id].w-a[x]-a[y];
			F[x].insert(mp(dlt/2+a[x],id));
			F[y].insert(mp(dlt/2+a[y],id));
		}
	}
	printf("%d\n",Ans[0]);
	for(int i=1;i<=Ans[0];i++)printf("%d ",Ans[i]);
	return 0;
}