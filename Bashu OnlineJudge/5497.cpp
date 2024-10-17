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
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const ull Mod=205891132094649ull;//3^30
const ull Delta=20202020202020ull;
const int N=3e6+5;
const int P=1e6+7;
const int S=729;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],f[S][S];
ull c[N],g[N];
struct edge{int to,next;ull val;}d[N*2];
void Add(ull x,int y){
	d[++cnt]=(edge){y,h[x%P],x};h[x%P]=cnt;
}
ull Rand(){
	return 1ull*rand()*(rand()*rand()+Delta)%Mod;
}
ull mod(ull x,ull y){
	ull ans=0,t=1;
	for(int i=0;i<5;i++){
		ans+=f[x%S][y%S]*t;
		x/=S;y/=S;t*=S;
	}
	return ans;
}
int Find(ull x){
	for(int i=h[x%P];i;i=d[i].next){
		if(d[i].val==x)return d[i].to;
	}
	return -2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	for(int i=0;i<S;i++){
		for(int j=0;j<S;j++){
			f[i][j]=f[i/3][j/3]*3+(i+j)%3;
		}
	}
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read()^Ans,y=read()^Ans;
		if(!c[x]){
			c[x]=Rand();
			Add(c[x],x);//once
			Add(mod(c[x],c[x]),x);//twice
		}
		g[i]=mod(g[y],c[x]);
		Ans=(g[i]==0)?-1:Find(g[i]);
		printf("%d\n",Ans);
	}
	return 0;
}