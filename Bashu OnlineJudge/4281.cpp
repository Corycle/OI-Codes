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
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m;
vector<int>e[N];
int a[N],deg[N],vis[N];
struct edge{int s,t;}E[N*3];
bool Check(int x,int y){
	return deg[x]!=deg[y]?deg[x]>deg[y]:x>y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		deg[E[i].s=read()]++;
		deg[E[i].t=read()]++;
	}
	for(int i=1;i<=m;i++){
		if(Check(E[i].s,E[i].t)){
			e[E[i].s].push_back(E[i].t);
		}
		else e[E[i].t].push_back(E[i].s);
	}
	ll Ans=0;
	for(int x=1;x<=n;x++){
		for(auto y:e[x])vis[y]=x;
		for(auto y:e[x]){
			for(auto z:e[y]){
				if(vis[z]==x)Ans+=max(max(a[x],a[y]),a[z]);
			}
		}
	}
	printf("%lld",Ans);
	return 0;
}