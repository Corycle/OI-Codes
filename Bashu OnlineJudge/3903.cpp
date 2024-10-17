#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,cnt,scc,tot;
int h[N],b[N],p[N],st[N],dfn[N],low[N];
map<string,int>id1,id2;
string a1[N],a2[N];
struct edge{
	int to,next;
}d[N*20];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	st[++top]=x;p[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(p[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(dfn[x]==low[x]){
		int k;scc++;
		do{
			k=st[top--];
			b[k]=scc;
			p[k]=0;
		}while(x!=k);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin>>a1[i]>>a2[i];
		id1[a1[i]]=i;
		id2[a2[i]]=i;
		Add(i,i+n);//女->男 
	}
	m=read();
	string A,B;
	for(int i=1;i<=m;i++){
		cin>>A>>B;
		Add(id2[B]+n,id1[A]);//男->女 
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i]!=b[i+n])printf("Safe\n");
		else printf("Unsafe\n");
	}
	return 0;
}