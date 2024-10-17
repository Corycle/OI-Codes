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
int n,m,cnt,h[200005],dis[200005],c[200005],vis[200005];
long long ans;
struct edge{
	int to,next,data;
}d[400005];
void hqq_add(int x,int y,int z){//y-x>=z  y>=x+z  x<=y-z
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
queue<int>q;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		int x=read(),a=read(),b=read();
		if(x==1){
			hqq_add(a,b,0);//b-a>=0
			hqq_add(b,a,0);//a-b>=0
		}
		if(x==2){
			hqq_add(a,b,1);//b-a>=1
			if(a==b){
				printf("-1");
				return 0;
			}
		}
		if(x==3)hqq_add(b,a,0);//a-b>=0
		if(x==4){
			hqq_add(b,a,1);//a-b>=1
			if(a==b){
				printf("-1");
				return 0;
			}
		}
		if(x==5)hqq_add(a,b,0);//b-a>=0
	}
	for(i=n;i>=1;i--){
		hqq_add(0,i,1);//i-0>=1;
	}
	memset(dis,-1,sizeof(dis));
	q.push(0);
	dis[0]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]<dis[x]+d[i].data){
//				cout<<x<<" "<<y<<" "<<d[i].data<<" "<<dis[y]<<" "<<dis[x]+d[i].data<<endl;
				dis[y]=dis[x]+d[i].data;
				c[y]++;
				if(c[y]>=n+1){
					printf("-1");
					return 0;
				}
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	for(i=1;i<=n;i++){
		if(dis[i]==-1){
			printf("-1");
			return 0;
		}
		ans+=dis[i];
	}
	printf("%lld",ans);
	return 0;
}