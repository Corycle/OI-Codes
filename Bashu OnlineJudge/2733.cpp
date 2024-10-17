#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=405;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tp,tot,cnt,scc;
int h[N],p[N],st[N],dfn[N],low[N],b[N];
struct edge{
	int to,next;
}d[M*2];
int Get(){
	char c;
	scanf("%c",&c);
	return read()+(c=='m'?1:0)*n;
}
void Prepare(){
	scc=cnt=tot=tp=0;
	memset(h,0,sizeof(h));
	memset(p,0,sizeof(p));
	memset(d,0,sizeof(d));
	memset(b,0,sizeof(b));
	memset(st,0,sizeof(st));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
}
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Tarjan(int x){
	dfn[x]=low[x]=++tot;
	p[x]=1;st[++tp]=x;
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
		int k=0;
		scc++;
		do{
			k=st[tp--];
			p[k]=0;
			b[k]=scc;
		}while(k!=x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		Prepare();
		n=read();m=read();
		for(int i=1;i<=m;i++){
			int x=Get(),y=Get();
			edge_add(x+n*2,y);
			edge_add(y+n*2,x);
		}
		for(int i=1;i<=n;i++){
			int x=i,y=i+n;
			edge_add(x,y+n*2);
			edge_add(y,x+n*2);
		}
		for(int i=1;i<=n*4;i++){
			if(!dfn[i])Tarjan(i);
		}
		int flag=1;
		for(int i=1;i<=n*2;i++){
//			cout<<b[i]<<" "<<b[i+n*2]<<endl;
			if(b[i]==b[i+n*2]){
				flag=0;
				break;
			}
		}
		if(flag)printf("GOOD\n");
		else printf("BAD\n");
	}
	return 0;
}