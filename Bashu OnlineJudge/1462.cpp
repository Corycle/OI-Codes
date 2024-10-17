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
int n,m,h[105],cnt,s1[105],s2[105],c[105],vis[105];
double p1,p2,p3,p[105],ans[105],maxx;
struct edge{
	int to,next;
}d[20005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
queue<int>q;
void bfs(){
	int i,j,k;
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(ans[y]<ans[x]*p[y]){
				ans[y]=ans[x]*p[y];
				if(vis[y]==0){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	scanf("%lf%lf%lf",&p1,&p2,&p3);
	p1=1-p1;
	p2=1-p2;
	p3=1-p3;
	for(i=1;i<=n;i++){
		int x=read();
		c[x]=read();
		if(c[x]==0)p[x]=p1;
		if(c[x]==1)p[x]=p2;
		if(c[x]==2)p[x]=p3;
		s1[x]=read();
		s2[x]=read();
		j=read();
		while(j--){
			int y=read();
			hqq_add(x,y);
		}
	}
	for(i=1;i<=n;i++){
		if(s1[i]==1){
			ans[i]=p[i];
			q.push(i);
			vis[i]=1;
		}
	}
	bfs();
	for(i=1;i<=n;i++){
		if(s2[i]==1){
			maxx=max(maxx,ans[i]);
		}
	}
	printf("%.2lf",maxx);
	return 0;
}