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
int n,m,head[1000005],to[4000005],next[4000005],s1,d[1000005],ans[1000005];
bool b[1000005];
queue<int>q;
void adde(int u,int v){
	to[s1]=v;
	next[s1]=head[u];
	head[u]=s1++;
}
int dfs(int u){
	if(ans[u])return ans[u];
	for(int i=head[u];i!=-1;i=next[i])
		if(d[u]-1==d[to[i]])ans[u]=(ans[u]+dfs(to[i]))%100003;
	return ans[u];
}
int main(){
	int i,j,k,f;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++){
		head[i]=-1;
		d[i]=0xffffff;
	}
	int u,v;
	for(i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		adde(u,v);
		adde(v,u);
	}
	d[1]=0;
	q.push(1);
	b[1]=1;
	while(!q.empty()){
		f=q.front();
		q.pop(),b[f]=0;
		for(i=head[f];i!=-1;i=next[i]){
			if(d[f]+1<d[to[i]]){
				d[to[i]]=d[f]+1;
				if(!b[to[i]]){
					q.push(to[i]);
					b[to[i]]=1;
				}
			}
		}  
	}
	ans[1]=1;
	for(i=1;i<=n;i++)printf("%d\n",dfs(i));
	return 0;
}