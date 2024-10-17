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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int tot=1,root=1,lst=1,ans,cnt;
int len[N],ch[N][30],fa[N];
int bj[N],c[N],vis[N],h[N],q[N];
struct edge{
	int to,next;
}d[N];
void edge_add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void SAM(int num){
	int x=lst,fx=++tot;
	len[fx]=len[x]+1;
	while(x&&!ch[x][num]){
		ch[x][num]=fx;
		x=fa[x];
	}
	if(!x)fa[fx]=root;
	else{
		int y=ch[x][num];
		if(len[y]==len[x]+1)fa[fx]=y;
		else{
			int fy=++tot;
			len[fy]=len[x]+1;
			for(int i=1;i<=26;i++){
				ch[fy][i]=ch[y][i];
			}
			fa[fy]=fa[y];
			fa[y]=fa[fx]=fy;
			while(x&&ch[x][num]==y){
				ch[x][num]=fy;
				x=fa[x];
			}
		}
	}
	lst=fx;
	bj[fx]=1;
}
void DFS(int x){
	vis[x]=1;
	c[x]=bj[x];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y])DFS(y);
		c[x]+=c[y];
	}
}
void Match(int m){
	int sum=0,p=root,num=0;
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		int x=s[i]-'a'+1;
		if(ch[p][x]){
			sum++;
			p=ch[p][x];
		}
		else{
			while(p&&!ch[p][x])p=fa[p];
			if(!p){
				p=root;
				sum=0;
			}
			else{
				sum=len[p]+1;
				p=ch[p][x];
			}
		}
		while(sum>m&&len[fa[p]]>=m){
			p=fa[p];
			sum=len[p];
		}
		if(sum>=m&&!vis[p]){
			ans+=c[p];
			sum=len[p];
			vis[p]=1;
			q[++num]=p;
		}
	}
	for(int i=1;i<=num;i++)vis[q[i]]=0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		SAM(s[i]-'a'+1);
	}
	for(int i=2;i<=tot;i++){
		edge_add(fa[i],i);
	}
	DFS(root);
	memset(vis,0,sizeof(vis));
	int T=read();
	while(T--){
		scanf("%s",s+1);
		int p=strlen(s+1);
		s[p*2]=s[p+1];
		for(int i=1;i<p;i++)s[i+p]=s[i];
		ans=0;Match(p);
		printf("%d\n",ans);
	}
	return 0;
}