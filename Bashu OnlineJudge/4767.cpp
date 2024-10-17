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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
map<int,int>V[N];
int n,m,q,fa[N],val[N];
struct Edge{int x,y,z;}e[N];
bool cmp(Edge A,Edge B){return A.z<B.z;}
int Find(int x,int Max=inf){
	while(x!=fa[x]&&val[x]<=Max)x=fa[x];
	return x;
}
bool Check(int x,int y,int Max){
	x=Find(x,Max);y=Find(y,Max);
	if(x==y)return true;
	if(!V[x].count(y))return false;
	return V[x][y]<=Max;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		e[i]=(Edge){x,y,z};
		G[x].push_back(y);
		G[y].push_back(x);
		V[x][y]=V[y][x]=0;
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=Find(e[i].x),y=Find(e[i].y);
		if(x==y)continue;
		if(G[x].size()>G[y].size())swap(x,y);
		fa[x]=y;val[x]=i;
		for(auto z:G[x]){
			z=Find(z);
			if(!V[y].count(z)){
				G[y].push_back(z);
				V[y][z]=V[z][y]=i;
			}
		}
		G[x].clear();
	}
	for(int i=1;i<=q;i++){
		int x=read(),y=read();
		if(Find(x)!=Find(y)){puts("-1");continue;}
		int l=0,r=m,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(x,y,mid)){
				ans=mid;r=mid-1;
			}
			else l=mid+1;
		}
		printf("%d\n",e[ans].z);
	}
	return 0;
}