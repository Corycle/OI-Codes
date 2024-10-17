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
int n,m,p[40005][20],cnt,h[40005],dis[40005];
bool dzh[40005];
struct edge{
	int to,next;
}d[4000005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void tree(int x){
	int i,j,k;
	for(i=h[x];i;i=d[i].next){
		if(!dzh[d[i].to]){
			dzh[d[i].to]=true;
			p[d[i].to][0]=x;
			dis[d[i].to]=dis[x]+1;
			tree(d[i].to);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int rt;
	n=read();
	memset(p,-1,sizeof(p));
	for(i=1;i<=n;i++){
		j=read();k=read();
		if(k==-1)rt=j;
		else{
			hqq_add(k,j);
			hqq_add(j,k);
		}
	}
	dzh[rt]=true;
	tree(rt);
	for(j=1;j<=int(log(40000)/log(2));j++){
		for(i=1;i<=40000;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
	m=read();
	while(m--){
		int f=2;
		i=read();j=read();
		if(dis[i]<dis[j])swap(j,i),f=1;
		k=int(log(dis[i])/log(2));
		for(k;k>=0;k--){
			if(dis[i]-(1<<k)>=dis[j])i=p[i][k];
		}
		if(i==j){
			printf("%d\n",f);
			continue;
		}
		printf("0\n");
	}
	return 0;
}