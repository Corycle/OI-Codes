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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N],vis[N];
struct Tree{int l,r,dis,data;}t[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int Merge(int x,int y){
	if(!x||!y)return x|y;
	if(t[x].data>t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	t[x].dis=t[x].r?t[t[x].r].dis+1:0;
	return x;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)t[i].data=read();
	m=read();
	char op[5];
	while(m--){
		scanf("%s",op);
		if(op[0]=='M'){
			int x=read(),y=read();
			if(vis[x]||vis[y])continue;
			x=Find(x);y=Find(y);
			if(x==y)continue;
			fa[x]=fa[y]=Merge(x,y);
		}
		if(op[0]=='D'){
			int x=read();
			if(vis[x]){
				printf("0\n");
				continue;
			}
			x=Find(x);
			int l=t[x].l,r=t[x].r;
			int y=Merge(l,r);
			fa[x]=fa[y]=y;
			printf("%d\n",t[x].data);
			t[x].l=t[x].r=0;vis[x]=1;
		}
	}
	return 0;
}