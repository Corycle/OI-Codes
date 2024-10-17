#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],rd[N],ans[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Prepare(){
	cnt=0;
	memset(h,0,sizeof(h));
	memset(rd,0,sizeof(rd));
	memset(ans,0,sizeof(ans));
}
void Topsort(){
	priority_queue<int>q;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i);
	while(q.size()){
		int x=q.top();
		q.pop();ans[++ans[0]]=x;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;rd[y]--;
			if(!rd[y])q.push(y);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		Prepare();
		n=read();m=read();
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			Add(y,x);rd[x]++;
		}
		Topsort();
		if(ans[0]!=n)printf("Impossible!\n");
		else{
			for(int i=n;i>=1;i--)printf("%d ",ans[i]);
			printf("\n");
		}
	}
	return 0;
}