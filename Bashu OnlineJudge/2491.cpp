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
#include<unordered_map>
#define ll long long
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll K;
pii P[N];
double f[N];
unordered_map<ll,int>pos;
int n,m,cnt,tot,h[N],nxt[N],lst[N];
struct edge{int to,next;double p;}d[N];
struct Edge{int x,y;ll s,t;double p;}E[N];
void Add(int x,int y,double z){d[++cnt]=(edge){y,h[x],z};h[x]=cnt;}
ll id(int t,int x){return t*n+x;}
int main(){
//	freopen("airplane.in","r",stdin);
//	freopen("airplane.out","w",stdout);
	m=read();n=read();K=read()+1;
	P[++tot]=mp(0,1);P[++tot]=mp(K,2);
	for(int i=1;i<=m;i++){
		E[i].x=read()+1;E[i].y=read()+1;
		E[i].s=read();E[i].t=read()+1;scanf("%lf",&E[i].p);
		P[++tot]=mp(E[i].s,E[i].x);P[++tot]=mp(E[i].t,E[i].y);
	}
	
	sort(P+1,P+tot+1);tot=unique(P+1,P+tot+1)-P-1;
	for(int i=1;i<=tot;i++)pos[id(P[i].fst,P[i].scd)]=i;
	for(int i=1;i<=m;i++)Add(pos[id(E[i].s,E[i].x)],pos[id(E[i].t,E[i].y)],E[i].p);
	for(int i=tot;i>=1;i--){nxt[i]=lst[P[i].scd];lst[P[i].scd]=i;}
	
	f[pos[id(K,2)]]=1;
	for(int x=tot;x>=1;x--){
		if(P[x].fst==K&&P[x].scd==2)continue;
		f[x]=f[nxt[x]];
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			f[x]=max(f[x],d[i].p*f[y]+(1-d[i].p)*f[nxt[x]]);
		}
	}
	printf("%.10lf\n",f[pos[id(0,1)]]);
	return 0;
}