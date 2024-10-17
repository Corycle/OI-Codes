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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,cnt,fa[N];
struct edge{int s,t;ll d;}e[N];
bool cmp(edge A,edge B){return A.d<B.d;}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].d=read();
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		fa[x]=y;Ans+=e[i].d;
	}
	int num=0;
	for(int i=1;i<=n;i++){
		if(fa[i]==i)num++;
	}
	if(num==1)printf("%lld",Ans);
	else printf("orz");
	return 0;
}