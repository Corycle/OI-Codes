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
int n,m,a[505][505],sx,sy,fx,fy,f[505][505],vis[505][505];
char c;
queue<int>qx,qy;
int s1[5]={0,1,-1,0,0};
int s2[5]={0,0,0,1,-1};
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(1){
		n=read();m=read();
		if(n==0)return 0;
		memset(a,0,sizeof(a));
		memset(f,0x3f,sizeof(f));
		memset(vis,0,sizeof(vis));
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				cin>>c;
				if(c=='@')a[i][j]=1;
				if(c=='#')a[i][j]=2;
			}
		}
		sx=read()+1;sy=read()+1;
		fx=read()+1;fy=read()+1;
		while(qx.size())qx.pop();
		while(qy.size())qy.pop();
		f[sx][sy]=0;
		qx.push(sx);
		qy.push(sy);
		while(qx.size()){
			int nx=qx.front(),ny=qy.front();
			qx.pop();qy.pop();
			vis[nx][ny]=0;
			for(i=1;i<=4;i++){
				int tx=nx+s1[i],ty=ny+s2[i];
				if(a[tx][ty]==0)continue;
				if(a[nx][ny]==a[tx][ty]){
					if(f[nx][ny]<f[tx][ty]){
						f[tx][ty]=f[nx][ny];
						if(vis[tx][ty]==0){
							vis[tx][ty]=1;
							qx.push(tx);
							qy.push(ty);
						}
					}
				}
				else{
					if(f[nx][ny]+1<f[tx][ty]){
						f[tx][ty]=f[nx][ny]+1;
						if(vis[tx][ty]==0){
							vis[tx][ty]=1;
							qx.push(tx);
							qy.push(ty);
						}
					}
				}
			}
		}
		printf("%d\n",f[fx][fy]);
	}
	return 0;
}