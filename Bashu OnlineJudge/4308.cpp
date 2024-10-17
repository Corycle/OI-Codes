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
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt1,cnt2;
int h1[N],h2[N],vis[N];ll a[N],dis[N];
struct edge{int to,next;}d1[N*5],d2[N*5];
void Add(int x,int y){
	d1[++cnt1]=(edge){y,h1[x]};h1[x]=cnt1;
	d2[++cnt2]=(edge){x,h2[y]};h2[y]=cnt2;
}
void Solve(){
	queue<int>q;
	for(int i=1;i<=n;i++){vis[i]=1;q.push(i);}
	while(q.size()){
		int x=q.front();ll tmp=a[x];vis[x]=0;q.pop();
		for(int i=h1[x];i;i=d1[i].next)tmp+=dis[d1[i].to];
		if(tmp<dis[x]){
			dis[x]=tmp;
			for(int i=h2[x];i;i=d2[i].next){
				int y=d2[i].to;
				if(!vis[y]){vis[y]=1;q.push(y);}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();dis[i]=read();
		int num=read();
		while(num--)Add(i,read());
	}
	Solve();
	printf("%lld",dis[1]);
	return 0;
}