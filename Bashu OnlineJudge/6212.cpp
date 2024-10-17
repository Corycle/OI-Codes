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
const int N=1e5+5;
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
int n,m,fa[N],dis[N],lst1[N],lst2[N];
int Find(int x){
	if(x==fa[x])return x;
	int tmp=fa[x];fa[x]=Find(fa[x]);dis[x]+=dis[tmp];
	return fa[x];
}
void Update(int x,int y,int dlt){
	int fx=Find(x),fy=Find(y);
	if(fx!=fy){dis[fx]=dis[y]-dis[x]-dlt;fa[fx]=fy;}
	else if(dis[y]-dis[x]!=dlt){printf("%d",abs(dlt-(dis[y]-dis[x])));exit(0);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int x=read();
			if(x){
				if(lst1[j])Update(lst1[j],i,x-lst2[j]);
				lst1[j]=i;lst2[j]=x;
			}
		}
	}
	puts("-1");
	return 0;
}