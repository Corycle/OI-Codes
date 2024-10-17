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
const int N=2005;
const int M=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char op[5];
int n,m,tp,cnt,tot,scc;
int h[N],p[N],b[N],st[N],dfn[N],low[N];
struct edge{
	int to,next;
}d[M*4];
void Add(int x,int y){
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
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read()+1,y=read()+1,data=read();
		scanf("%s",op);
		if(op[1]=='N'){//AND
			if(data==0){Add(x+n,y);Add(y+n,x);}
			if(data==1){Add(x+n,y+n);Add(y+n,x+n);}
		}
		if(op[1]=='R'){//OR
			if(data==0){Add(x,y);Add(y,x);}
			if(data==1){Add(x,y+n);Add(y,x+n);}
		}
		if(op[1]=='O'){//XOR
			if(data==0){
				Add(x,y);Add(y,x);
				Add(x+n,y+n);Add(y+n,x+n);
			}
			if(data==1){
				Add(x,y+n);Add(y,x+n);
				Add(x+n,y);Add(y+n,x);
			}
		}
	}
	for(int i=1;i<=n*2;i++){
		if(!dfn[i])Tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(b[i]==b[i+n]){
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}