#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,vis[45][45],a[45][45],ans;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	int x=1,y=1;
	ans=a[1][1];
	vis[1][1]=1;
	while(x!=n||y!=m){
		k=0;j=0;
		for(i=1;i<=4;i++){
			int fx=x+dx[i],fy=y+dy[i];
			if(vis[fx][fy]==0&&j<a[fx][fy]){
				k=i;
				j=a[fx][fy];
			}
		}
		ans+=j;
		x=x+dx[k];
		y=y+dy[k];
		vis[x][y]=1;
	}
	printf("%d",ans);
	return 0;
}