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
int n,m,p[200005][20],cnt,h[200005],dis[200005];
struct edge{
	int to,next;
}d[200005];
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void tree(int x){
	int i,j,k;
	for(i=h[x];i;i=d[i].next){
		dis[d[i].to]=dis[x]+1;
		tree(d[i].to);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	memset(p,-1,sizeof(p));
	for(i=1;i<n;i++){
		j=read();k=read();
		hqq_add(j,k);
		p[k][0]=j;
	}
	for(i=1;i<=n;i++){
		if(p[i][0]==-1){
			dis[i]=1;
			tree(i);
			break;
		}
	}
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i<=n;i++){
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
		}
	}
	while(m--){
		i=read();j=read();
		if(dis[i]<dis[j])swap(j,i);
		k=int(log(dis[i])/log(2));
		for(k;k>=0;k--){
			if(dis[i]-(1<<k)>=dis[j])i=p[i][k];
		}
		if(i==j){
			printf("%d\n",i);
			continue;
		}
		k=int(log(dis[i])/log(2));
		for(k;k>=0;k--){
			if(p[i][k]!=p[j][k]){
				i=p[i][k];j=p[j][k];
			}
		}
		printf("%d\n",p[i][0]);
	}
	return 0;
}