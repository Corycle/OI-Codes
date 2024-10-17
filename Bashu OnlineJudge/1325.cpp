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
struct edge{
	int to,next;
}d[20005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,cnt,h[105],fs,fn,p[105];
int read(){
	char c=getchar();
	int s=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		s=s*10+c-'0';
		c=getchar();
	}
	return s;
}
void hqq_add(int x,int y){
	cnt++;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
void hqq_dfs(int rt){
	int i,j,k;
	p[rt]=1;
	for(i=h[rt];i;i=d[i].next){
		j=d[i].to;
		if(p[j]==1)continue;
		hqq_dfs(j);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	while(1){
		j=read();k=read();
		if(j==0&&k==0)break;
		hqq_add(j,k);
		hqq_add(k,j);
	}
	fs=read();fn=read();
	for(i=1;i<=n;i++){
		if(i==fs||i==fn)continue;
		memset(p,0,sizeof(p));
		p[i]=1;
		hqq_dfs(fs);
		if(p[fn]==0){
			printf("%d",i);
			return 0;
		}
	}
	printf("No solution");
	return 0;
}