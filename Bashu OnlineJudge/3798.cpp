#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
struct node{
	int dps,hp;
	double p;
}d[105];
int n;
bool cmp(node x,node y){
	return x.p>y.p;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		d[i].dps=read();
		d[i].hp=read();
		d[i].p=(double)d[i].dps/d[i].hp;
	}
	sort(d+1,d+n+1,cmp);
	int ans=0,t=0;
	for(i=1;i<=n;i++){
		t+=d[i].hp;
		ans+=t*d[i].dps;
	}
	printf("%d",ans);
	return 0;
}