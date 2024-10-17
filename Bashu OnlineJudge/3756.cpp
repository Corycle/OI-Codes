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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,tot,c[N],fa[N],son[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Merge(int x,int y){
	x=Find(x);y=Find(y);
	if(x!=y){
		fa[y]=x;
		if(!son[x]||!son[y])son[x]|=son[y];
		if(son[x]&&son[y])Merge(son[x],son[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){int x=read(),y=read();G[x].push_back(y);if(!son[x])son[x]=y;}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int x=1;x<=n;x++){int lst=0;for(auto y:G[x]){if(lst)Merge(lst,y);lst=y;}}
	for(int i=1;i<=n;i++)printf("%d\n",c[Find(i)]?c[Find(i)]:(c[Find(i)]=++tot));
	return 0;
}
