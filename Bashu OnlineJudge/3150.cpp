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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,tot;
int g[N][N],p[N],vis[N];
struct ques{
	int t,dis,sx,sy,tx,ty;
}a[N];
bool DFS(int x){
	for(int y=x+1;y<=n;y++){
		if(g[x][y]&&!vis[y]){
			vis[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
int Hungary(){
	int tmp=0;
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(DFS(i))tmp++;
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		memset(g,0,sizeof(g));
		n=read();
		for(int i=1;i<=n;i++){
			a[i].t=read()*60+read();
			a[i].sx=read();a[i].sy=read();
			a[i].tx=read();a[i].ty=read();
			a[i].dis=abs(a[i].sx-a[i].tx)+abs(a[i].sy-a[i].ty);
			for(int j=i-1;j>=1;j--){
				int dis=abs(a[i].sx-a[j].tx)+abs(a[i].sy-a[j].ty);
				if(a[j].t+a[j].dis+dis<a[i].t)g[j][i]=1;
			}
		}
		int ans=n-Hungary();
		printf("%d\n",ans);
	}
	return 0;
}