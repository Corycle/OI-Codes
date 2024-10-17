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
int n,m,ki,h[105],cnt,vis[105],dis[105],c[105];
string oi;
struct edge{
	int to,next,data;
}d[10005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
queue<int>q;
int spfa(int s){
	int i,j,k;
	while(q.size())q.pop();
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(c,0,sizeof(c));
	q.push(s);
	vis[s]=1;dis[s]=0;
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]>dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				c[y]++;
				if(c[y]==n+2)return 0;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
//	for(i=0;i<=n;i++)cout<<dis[i]<<endl;
	for(i=1;i<=n;i++){
		if(dis[i]==-0x3f3f3f3f)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(1){
		n=read();if(!n)break;
		m=read();
		memset(d,0,sizeof(d));
		memset(h,0,sizeof(h));
		cnt=0;
		int s=n+1;
		for(i=1;i<=m;i++){
			j=read();k=read();
			cin>>oi;ki=read();
			if(oi=="gt"){
				hqq_add(j+k,j-1,-ki-1);//dis[k]-dis[j-1]<ki
			}
			if(oi=="lt"){
				hqq_add(j-1,j+k,ki-1);//dis[j-1]-dis[k]<-ki
			}
		}
		for(i=0;i<=n;i++){
			hqq_add(s,i,0);//dis[i]-dis[s]<0
		}
		if(spfa(s))printf("lamentable kingdom\n");
		else printf("successful conspiracy\n");
	}
	return 0;
}