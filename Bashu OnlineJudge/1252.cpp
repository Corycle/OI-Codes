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
int n,m,a[1005][1005],dis[1005],c[1005],vis[1005];
queue<int>q;
int spfa(){
	int i,j,k;
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	q.push(0);
	while(q.size()){
		i=q.front();vis[i]=0;
		q.pop();
		for(j=1;j<=n;j++){
			if(dis[i]+a[i][j]<dis[j]){
				dis[j]=dis[i]+a[i][j];
				c[j]++;
				if(c[j]==n)return 0;
				if(!vis[j]){
					vis[j]=1;
					q.push(j);
				}
			}
		}
	}
	for(i=1;i<=n;i++){
		if(dis[i]==0x3f3f3f3f)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	memset(a,0x3f,sizeof(a));
	for(i=1;i<=m;i++){
		j=read();k=read();
		a[k][j]=read();//j-k<=a[k][j]
	}
	for(i=1;i<=n;i++){
		a[0][i]=0;
	}
	if(spfa()){
		k=0;
		for(i=1;i<=n;i++)k=min(k,dis[i]);
		if(k<0)for(i=1;i<=n;i++)dis[i]-=k;
		for(i=1;i<=n;i++)printf("%d\n",dis[i]);
	}
	else printf("NO SOLUTION");
	return 0;
}