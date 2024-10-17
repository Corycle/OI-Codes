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
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,tot;
int h[N],fa[N],dis[N];
struct edge{
	int to,next,data;
}d[N*2];
struct Trie{
	int ch[2],flag;
}t[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
void DFS(int x){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		dis[y]=dis[x]^d[i].data;
		fa[y]=x;DFS(y);
	}
}
void Insert(int num){
	int p=0;
	for(int i=30;i>=0;i--){
		int x=(num>>i)&1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
	t[p].flag=1;
}
int Ask(int num){
	int p=0,ans=0;
	for(int i=30;i>=0;i--){
		int x=(num>>i)&i;
		if(t[p].ch[x^1]){
			ans+=(1<<i);
			p=t[p].ch[x^1];
		}
		else p=t[p].ch[x];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read()+1,y=read()+1,z=read();
		Add(x,y,z);Add(y,x,z);
	}
	DFS(1);
	int ans=0;
	for(int i=1;i<=n;i++)Insert(dis[i]);
	for(int i=1;i<=n;i++)ans=max(ans,Ask(dis[i]));
	printf("%d",ans);
	return 0;
}