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
#define ld long double
#define pii pair<ll,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const ll inf=1e18;
const int N=1e5+5;
const int M=350;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,f[N];
int n,m,num;
int a[N],t[N],st[N],ed[N],pos[N];
bool cmp(int x,int y){return a[x]<a[y];}
struct Block{
	ll k,b;
	int l,r,p[M+5];
	ll Calc(int x){return k*a[x]+b+f[x];}
	ld Slope(int x,int y){
		return f[x]==f[y]?0:(a[x]!=a[y]?(ld)(f[y]-f[x])/(a[y]-a[x]):(f[y]>f[x]?inf:-inf));
	}
	void Build(int id){
		for(int i=st[id];i<=ed[id];i++)f[i]+=k*a[i]+b;k=b=0;l=1;r=0;
		for(int i=st[id];i<=ed[id];i++){
			while(l<r&&Slope(p[r-1],p[r])<Slope(p[r],t[i]))r--;
			p[++r]=t[i];
		}
	}
	pii Query(){
		while(l<r&&Calc(p[l])<=Calc(p[l+1]))l++;
		return mp(Calc(p[l]),p[l]);
	}
}blocks[M];
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(n,ed[num-1]+M);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
	for(int i=1;i<=n;i++)t[i]=i;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++)a[i]=f[i]=read();
	for(int i=1;i<=num;i++){
		sort(t+st[i],t+ed[i]+1,cmp);
		blocks[i].Build(i);
	}
	while(1){
		pii tmp=mp(0,0);
		for(int i=1;i<=num;i++)tmp=max(tmp,blocks[i].Query());
		if(tmp.fst<=0)break;
		Ans+=tmp.fst;f[tmp.scd]=-inf;
		for(int i=1;i<pos[tmp.scd];i++)blocks[i].b+=a[tmp.scd];
		for(int i=st[pos[tmp.scd]];i<tmp.scd;i++)f[i]+=a[tmp.scd];
		for(int i=tmp.scd+1;i<=ed[pos[tmp.scd]];i++)f[i]+=a[i];
		for(int i=pos[tmp.scd]+1;i<=num;i++)blocks[i].k++;
		blocks[pos[tmp.scd]].Build(pos[tmp.scd]);
	}
	printf("%lld",Ans);
	return 0;
}
