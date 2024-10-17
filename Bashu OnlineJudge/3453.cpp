/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define set_it multiset<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Min,flag,h[N],f[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
multiset<int>G[N];
void DFS(int x,int fa){
	G[x].clear();
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		if(!flag)return;
		G[x].insert(f[y]+1);
	}
	int Flag=0;
	if((x==1&&G[x].size()&1)||(x!=1&&!(G[x].size()&1)))G[x].insert(0);
	while(!G[x].empty()){
		set_it p=G[x].begin();
		int t=(*p);G[x].erase(p);
		p=G[x].lower_bound(Min-t);
		if(x==1){
			if(p==G[x].end()){flag=0;return;}
			G[x].erase(p);
		}
		else{
			if(p==G[x].end()&&Flag){flag=0;return;}
			if(p==G[x].end()){f[x]=t;Flag=1;}
			if(p!=G[x].end())G[x].erase(p);
		}
	}
}
bool Check(int x){
	for(int i=1;i<=n;i++)f[i]=0;
	flag=1;Min=x;DFS(1,0);
	return flag;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	int l=1,r=n,ans=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}