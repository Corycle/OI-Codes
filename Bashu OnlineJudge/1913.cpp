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
const int N=500005;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],fa[N],val[N],tag[N];
struct edge{int to,next,id;}d[N*2];
int Random(){return rand()*rand()+rand();}
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
void Add(int x,int y,int id){d[++cnt]=(edge){y,h[x],id};h[x]=cnt;}
void DFS(int x,int Fa){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==Fa)continue;
		DFS(y,x);
		tag[x]^=tag[y];
		val[d[i].id]=tag[y];
	}
}
struct Line_Basis{
	int p[M];
	void Clear(){memset(p,0,sizeof(p));}
	int Insert(int x){
		for(int i=30;i>=0;i--){
			if((x>>i)&1){
				if(!p[i]){p[i]=x;return 1;}
				x^=p[i];
			}
		}
		return 0;
	}
}F;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	srand(time(NULL));
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		val[i]=Random();
		if(Find(x)==Find(y)){
			tag[x]^=val[i];
			tag[y]^=val[i];
		}
		else{
			fa[Find(x)]=Find(y);
			Add(x,y,i);Add(y,x,i);
		}
	}
	DFS(1,0);
	int T=read();
	while(T--){
		F.Clear();
		int num=read(),flag=1;
		for(int i=1;i<=num;i++){
			flag&=F.Insert(val[read()^Ans]);
		}
		Ans+=flag;
		if(flag)puts("Connected");
		else puts("Disconnected");
	}
	return 0;
}