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
const int inf=0x3f3f3f3f;
int n,o,h,r,cnt;
int next[4000005],end[4000005],last[4000005],len[4000005],dis[10005];
bool vis[10005];
deque<int>q;
void hqq_add(int a,int b,int l){
	end[++cnt]=b;
	len[cnt]=l;
	next[cnt]=last[a];
	last[a]=cnt;
}
void spfa(){
	int i,j,k;
	int y,t,x;
	memset(dis,0x3f,sizeof(dis));
	q.push_back(0);dis[0]=h;
	while(q.size()){
		x=q.front();
		q.pop_front();
		vis[x]=0;
		t=last[x];
		while(t!=0){
			y=end[t];
			if(dis[x]+len[t]<dis[y]){
				dis[y]=dis[x]+len[t];
				if(!vis[y]){
					vis[y]=1; 
//					q.push(y);
					if(q.size()){
						if(dis[y]<dis[q.front()]){
							q.push_front(y);
						}
						else q.push_back(y);
					}
					else q.push_back(y);
				}
			} 
			t=next[t];
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int a,b;
	n=read();o=read();h=read();r=read();
	for(i=1;i<=n;i++)hqq_add(0,i,0);
	for(i=1;i<=r;i++){
		a=read();b=read();
		hqq_add(b,a,0);
		if(a>b){
			for(j=b+1;j<a;j++)hqq_add(a,j,-1);
		}
		else{
			for(j=a+1;j<b;j++)hqq_add(a,j,-1);
		}
	}
	spfa();
	for(i=1;i<=n;i++){
		printf("%d\n",dis[i]);
	}
	return 0;
}