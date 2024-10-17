#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll T,Lx,Rx,Ly,Ry,f[N][1<<16];
ll t[N],lx[N],rx[N],ly[N],ry[N];
void Solve(ll x,ll a[]){
	for(ll i=0;i<=60;i++){
		if((x>>i)&1)a[i]=1;
		else a[i]=0;
	}
}
ll Sta(ll t,ll sta,ll x,ll y){
	ll s=0;
	for(ll i=0;i<16;i++){
		if(!((sta>>i)&1))continue;
		ll fx=(i>>0)&1,tx=(i>>1)&1;
		ll fy=(i>>2)&1,ty=(i>>3)&1;
		if((fx&&x>rx[t])||(tx&&x<lx[t]))continue;
		if((fy&&y>ry[t])||(ty&&y<ly[t]))continue;
		fx=(fx&(x==rx[t]));tx=(tx&(x==lx[t]));
		fy=(fy&(y==ry[t]));ty=(ty&(y==ly[t]));
		s|=(1<<(fx+(tx<<1)+(fy<<2)+(ty<<3)));
	}
	return s;
}
ll DFS(ll x,ll sta){
	if(!sta)return 0;
	if(x==-1)return 1;
	if(f[x][sta]!=-1)return f[x][sta];
	ll ans=0;
	if(!t[x])ans=DFS(x-1,Sta(x,sta,0,0));
	else{
		ans+=DFS(x-1,Sta(x,sta,1,1));
		ans+=DFS(x-1,Sta(x,sta,1,0)|Sta(x,sta,0,1));
	}
	return f[x][sta]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	Solve(T=read(),t);
	Solve(Lx=read(),lx);
	Solve(Rx=read(),rx);
	Solve(Ly=read(),ly);
	Solve(Ry=read(),ry);
	memset(f,-1,sizeof(f));
	DFS(61,1<<15);
	printf("%lld",f[61][1<<15]);
	return 0;
}