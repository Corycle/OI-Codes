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
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Sum;
int h[N],a[N],pre[N],Ans[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS1(int x,int fa){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS1(y,x);
		int f=min(a[x],a[y]);
		Sum+=f*2;a[x]-=f;a[y]-=f;
		if(a[y])pre[x]=y;
	}
}
void DFS2(int x,int fa){
	Ans[x]=Sum;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		if(a[x]){Sum++;a[x]--;DFS2(y,x);Sum--;a[x]++;}
		else if(!pre[y]){Sum--;a[y]++;DFS2(y,x);Sum++;a[y]--;}
		else{Sum++;a[pre[y]]--;DFS2(y,x);Sum--;a[pre[y]]++;}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read()+1,y=read()+1;
		Sum+=2;a[x]--;a[y]--;
		Add(x,y);Add(y,x);
	}
	DFS1(1,0);DFS2(1,0);
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}