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
int n,m,cnt,r[50],h[50],dis[50],vis[50],num[50],c[50];
bool flag;
struct edge{
	int to,next,data;
}d[1000005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	d[cnt].data=z;
	h[x]=cnt;
}
queue<int>q;
int spfa(int sum){
	int i,j,k;
	memset(vis,0,sizeof(vis));
	memset(dis,-0x3f,sizeof(dis));
	memset(c,0,sizeof(c));
	while(q.size())q.pop();
	vis[24]=1;
	dis[24]=0;
	q.push(24);
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[y]<dis[x]+d[i].data){
				dis[y]=dis[x]+d[i].data;
				c[y]++;
				if(c[y]>=1000){
					return 0;
				}
				if(vis[y]==0){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	for(i=0;i<=23;i++){
		if(dis[i]==-0x3f3f3f3f)return 0;
	}
	if(dis[23]==sum){
		flag=true;
		return 1;
	}
	return 0;
}
int solve(int sum){
	memset(h,0,sizeof(h));
	int i,j,k;
	cnt=0;
	hqq_add(24,0,0);
	hqq_add(0,24,-num[0]);
	hqq_add(24,23,sum);
	for(i=1;i<=23;i++){
		hqq_add(i-1,i,0);
		hqq_add(i,i-1,-num[i]);
	}
	for(i=0;i<=23;i++){
		if(i>=8)hqq_add(i-8,i,r[i]);
		else hqq_add(i+16,i,r[i]-sum);
	}
	if(spfa(sum))return 1;
	return 0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=0;i<=23;i++)r[i]=read();
	m=read();
	for(i=1;i<=m;i++){
		j=read();
		num[j]++;
	}
	for(i=0;i<=m;i++){
		if(solve(i))break;
	}
	if(flag)printf("%d",i);
	else printf("No Solution!");
	return 0;
}