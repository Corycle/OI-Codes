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
const int N=1<<20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
ll d[N*20];
vector<int>G[N];
int n,m,tot,a[N];
int ID(int i,int j){
	int id=1ll*(i-1)*(m+1)+j;
	for(auto y:G[id%N])if(d[y]==id)return y;
	d[++tot]=id;G[id%N].push_back(tot);
	return tot;
}
struct BIT{
	int c[N*20];
	int lowbit(int x){return x&(-x);}
	int Ask(int x,int y){int ans=0;for(int i=x;i>=1;i-=lowbit(i))ans+=c[ID(i,y)];return ans;}
	void Add(int x,int y,int v){for(int i=x;i<=n;i+=lowbit(i))for(int j=y;j<=m;j+=lowbit(j))c[ID(i,j)]+=v;}
	int Query(int l,int r,int k){int ans=0;for(int i=16;i>=0;i--){int tmp=Ask(r,ans+(1<<i))-Ask(l-1,ans+(1<<i));if(k>tmp){k-=tmp;ans+=(1<<i);}}return ans;}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=2e5;
	for(int i=1;i<=n;i++){a[i]=read()+1;tree.Add(i,a[i],1);}
	int T=read();
	while(T--){
		scanf("%s",s);
		int x=read(),y=read();
		if(s[0]=='Q')printf("%d\n",tree.Query(x,y,read()));
		if(s[0]=='C'){tree.Add(x,a[x],-1);a[x]=y+1;tree.Add(x,a[x],1);}
	}
	return 0;
}