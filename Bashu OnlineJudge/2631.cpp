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
int n,m;
double d[55][55],dis[55][55][55];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=50;i++){
		for(j=1;j<=50;j++){
			d[i][j]=0x3f3f3f3f;
		}
	}
	for(i=1;i<=50;i++){
		for(j=1;j<=50;j++){
			for(k=1;k<=50;k++){
				dis[i][j][k]=0x3f3f3f3f;
			}
		}
	}
	for(i=1;i<=m;i++){
		j=read();k=read();
		double t;
		scanf("%lf",&t);
		dis[j][k][1]=d[j][k]=min(dis[j][k][1],t);
	}
	for(int t=2;t<=n;t++){
		for(k=1;k<=n;k++){
			for(i=1;i<=n;i++){
				for(j=1;j<=n;j++){
					dis[i][j][t]=min(dis[i][j][t],dis[i][k][t-1]+dis[k][j][1]);
					if(dis[i][j][t]!=0x3f3f3f3f)d[i][j]=min(d[i][j],dis[i][j][t]/t);
				}
			}
		}
	}
	int q=read();
	while(q--){
		j=read();k=read();
		if(d[j][k]==0x3f3f3f3f)printf("OMG!\n");
		else printf("%.3lf\n",d[j][k]);
	}
	
	return 0;
}