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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=4e4+5;
const int N=1e6+5;
const int M=22;
ull read(){
	ull s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ull a[N];
int n,m,cnt,fa[N],dep[N];
struct Line_Basis{
	ull p[64];
	int b[64];
	void Insert(ull x,int depth){
		for(int i=63;i>=0;i--){
			if((x>>i)&1){
				if(!p[i]){p[i]=x;b[i]=depth;break;}
				else if(depth>b[i]){swap(p[i],x);swap(b[i],depth);}
				x^=p[i];
			}
		}
	}
	ull Query(int depth){
		ull x=0;
		for(int i=63;i>=0;i--){
			if(b[i]<depth)continue;
			if((x^p[i])>x)x^=p[i];
		}
		return x;
	}
}F[N];
int main(){
//	freopen("squirrel.in","r",stdin);
//	freopen("squirrel.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		fa[i]=read();a[i]=read();
		dep[i]=dep[fa[i]]+1;
		F[i]=F[fa[i]];
		F[i].Insert(a[i],dep[i]);
	}
	for(int i=1;i<=m;i++){
		int op=read();
		if(op==0){
			int x=read(),d=read();
			printf("%llu\n",F[x].Query(dep[x]-d));
		}
		if(op==1){
			fa[++n]=read();a[n]=read();
			dep[n]=dep[fa[n]]+1;
			F[n]=F[fa[n]];
			F[n].Insert(a[n],dep[n]);
		}
	}
	return 0;
}