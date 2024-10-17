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
const int N=5e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char c;
int n,m,cnt,h[N];
struct edge{int to,next;char c;}d[N];
void Add(int x,int y,char c){d[++cnt]=(edge){y,h[x],c};h[x]=cnt;}
struct Trie{
	int tot=1,root=1,sum[N];
	void Insert(){
		int p=1;c=getchar();
		for(int len=1;c!='\n';c=getchar(),len++){
			int y=0;
			for(int i=h[p];i;i=d[i].next){
				if(c==d[i].c){y=d[i].to;break;}
			}
			if(!y)Add(p,y=++tot,c);p=y;sum[p]++;
			Ans=max(Ans,1ll*len*sum[p]);
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
//	c=getchar();
//	while(c!='\n')c=getchar();
	for(int i=1;i<=n;i++)tree.Insert();
	printf("%lld",Ans);
	return 0;
}