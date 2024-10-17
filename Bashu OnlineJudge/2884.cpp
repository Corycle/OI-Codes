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
int n,m,a[505][505],dis[505][505];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	memset(dis,0x3f,sizeof(dis));
	memset(a,0x3f,sizeof(a));
	for(i=1;i<=m;i++){
		j=read();k=read();
		a[j][k]=a[k][j]=dis[j][k]=dis[k][j]=min(a[j][k],read());
	}
	for(i=1;i<=n;i++)a[i][i]=dis[i][i]=0;
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	int x=0,y=0,z=0x3f3f3f3f;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j]==0x3f3f3f3f)continue;
			if(z>a[i][j]/2+dis[1][i]+dis[j][n]){
				z=a[i][j]/2+dis[1][i]+dis[j][n];
				x=i;y=j;
			}
		}
	}
	printf("%d %d\n%d",x,y,z);
	return 0;
}