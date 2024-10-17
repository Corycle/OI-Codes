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
int T,n,m,a[10][10],num,use[100][100];
void DFS(int x,int y,int z){
	if(x>n){
		num=max(num,z);
		return;
	}
	int xx=x,yy=y+1;
	if(yy>m){
		xx++;
		yy=1;
	}
	if(!use[x-1][y]&&!use[x][y-1]&&!use[x-1][y-1]&&!use[x-1][y+1]){
		use[x][y]=1;
		DFS(xx,yy,z+a[x][y]);
		use[x][y]=0;
	}
	DFS(xx,yy,z);
}
int main(){
	int T,i,j,k;
	T=read();
	while(T--) {
		num=0;
		n=read();m=read();
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				a[i][j]=read();
			}	 
		}
		DFS(1,0,0);
		printf("%d\n",num);
	}
	return 0;
}