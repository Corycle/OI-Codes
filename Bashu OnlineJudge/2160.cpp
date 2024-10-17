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
#include<bitset>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=55;
const int M=2505;
int read(){
	int S=0,dis2=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')dis2=-1;c=getchar();}
	while(c>='0'&&c<='9'){S=S*10+c-'0';c=getchar();}
	return S*dis2;
}
int n,m,s,t,num,cnt,cnt1,cnt2;
int h1[N],h2[N],vis[N],dis[N];
struct node{
	int x,g,f;
	bitset<N>vis;
	string step;
}st,ans;
struct edge{
	int to,next,data;
}d1[M],d2[M];
bool operator<(node x,node y){
	if(x.f!=y.f)return x.f>y.f;
	return x.step>y.step;
}
void Add1(int x,int y,int z){
	d1[++cnt1]=(edge){y,h1[x],z};
	h1[x]=cnt1;
}
void Add2(int x,int y,int z){
	d2[++cnt2]=(edge){y,h2[x],z};
	h2[x]=cnt2;
}
void SPFA(){
	queue<int>q;
	memset(dis,0x3f,sizeof(dis));
	q.push(t);dis[t]=0;
	while(q.size()){
		int x=q.front();
		q.pop();vis[x]=0;
		for(int i=h2[x];i;i=d2[i].next){
			int y=d2[i].to;
			if(dis[y]>dis[x]+d2[i].data){
				dis[y]=dis[x]+d2[i].data;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
}
void A_star(){
	priority_queue<node>q;
	st.x=s;st.f=dis[s];
	st.g=0;st.vis[s]=1;
	st.step=(char)(s);
	q.push(st);
	while(q.size()){
		node x=q.top();
		q.pop();
		if(x.x==t)cnt++;
		if(cnt==num){
			for(int i=0;i<x.step.length()-1;i++)
				printf("%d-",x.step[i]);
			printf("%d",x.x);
			return;
		}
		for(int i=h1[x.x];i;i=d1[i].next){
			if(x.vis[d1[i].to])continue;
			node y=x;
			y.x=d1[i].to;
			y.vis[y.x]=1;
			y.g=x.g+d1[i].data;
			y.f=y.g+dis[y.x];
			y.step=x.step+char(y.x);
			q.push(y);
		}
	}
	printf("No");
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();num=read();
	s=read();t=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add1(x,y,z);
		Add2(y,x,z);
	}
	SPFA();A_star();
	return 0;
}