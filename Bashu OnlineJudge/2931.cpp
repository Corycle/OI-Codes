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
int n,cnt,h[1000005],qh,qt;
struct hqq_edge{
	int to,next,data;
}d[2000005];
void hqq_add(int x,int y,int z){
	cnt++;
	d[cnt].data=z;
	d[cnt].to=y;
	d[cnt].next=h[x];
	h[x]=cnt;
}
long long q[1000005],sum[1000005],fa[1000005],v[1000005],ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		hqq_add(x,y,z);
		hqq_add(y,x,z);
	}
	qh=qt=1;
	fa[1]=-1;
	q[1]=1;
	while(qh<=qt){
		int x=q[qh++];
		for(i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(fa[y]!=0)continue;
			q[++qt]=y;
			fa[y]=x;
			sum[y]=1;
			v[y]=d[i].data;
		}
	}
	for(i=qt;i>=2;i--){
		int x=q[i];
		sum[fa[x]]+=sum[x];
		ans+=v[x]*abs(sum[x]*2-n);
	}
	printf("%lld",ans);
	return 0;
}