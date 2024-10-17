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
int tot=1,lst=1,root=1,ans,cnt;
int ch[N][30],fa[N],len[N],f[N],h[N],vis[N];
struct edge{
	int to,next;
}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void SAM(int num,int p){
	int x=lst,fx=++tot;
	len[fx]=len[x]+1;
	f[fx]=p;
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
			f[fy]=inf;
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
}
void DFS(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(!vis[y])
		DFS(y);
		if(f[x]&&f[y])f[x]=min(f[x],f[y]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;i++){
		SAM(s[i]-'a'+1,i);
	}
	for(int i=1;i<=tot;i++){
		Add(fa[i],i);
	}
	DFS(root);
	for(int i=1,j;i<=n;i=j){
		int p=root;
		for(j=i;j<=n;j++){
			int x=s[j]-'a'+1;
			if(!ch[p][x]||(ch[p][x]&&f[ch[p][x]]-(j-i)>=i))break;
			p=ch[p][x];
		}
		if(i==j)printf("-1 %d ",s[j++]);
		else printf("%d %d ",j-i,f[p]-(j-i));
	}
	return 0;
}