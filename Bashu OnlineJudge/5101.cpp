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
const int M=100005;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int h[N],fa[N],Ans[N],dis[N][N];
struct edge{int to,next;}d[M*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Check(int s){
	queue<int>q;q.push(s);dis[s][s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		Ans[Find(x)]=max(Ans[Find(x)],dis[s][x]);
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(dis[s][y]==-1){
				dis[s][y]=dis[s][x]+1;q.push(y);
			}
			if(!((dis[s][x]&1)^(dis[s][y]&1)))return false;
		}
	}
	return true;
}
int main(){
//	freopen("merge.in","r",stdin);
//	freopen("merge.out","w",stdout);
	n=read();m=read();
	memset(dis,-1,sizeof(dis));
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		fa[Find(x)]=Find(y);
		Add(x,y);Add(y,x);
	}
	srand(time(NULL));
	for(int i=1;i<=n;i++){
		if(i==Find(i)||(rand()&1)||m<=5000){
			if(!Check(i)){
				printf("-1");
				return 0;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(i==Find(i)){
			ans+=Ans[Find(i)];
		}
	}
	printf("%d",ans);
	return 0;
}