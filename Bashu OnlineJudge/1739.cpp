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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int fa[N],Minx[N],Maxx[N],Miny[N],Maxy[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		Minx[i]=Maxx[i]=read();
		Miny[i]=Maxy[i]=read();
	}
	for(int i=1;i<=m;i++){
		int x=Find(read());
		int y=Find(read());
		if(x==y)continue;fa[y]=x;
		Minx[x]=min(Minx[x],Minx[y]);
		Maxx[x]=max(Maxx[x],Maxx[y]);
		Miny[x]=min(Miny[x],Miny[y]);
		Maxy[x]=max(Maxy[x],Maxy[y]);
	}
	int Ans=inf;
	for(int i=1;i<=n;i++){
		if(fa[i]==i){
			Ans=min(Ans,((Maxx[i]-Minx[i])+(Maxy[i]-Miny[i]))*2);
		}
	}
	printf("%d",Ans);
	return 0;
}