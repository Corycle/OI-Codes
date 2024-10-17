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
int n,m,ans,cnt;
int h[N],cd[N],rd[N],sum[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
int DFS(int x){
	if(sum[x])return sum[x];
	if(rd[x]&&!cd[x])sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		sum[x]+=DFS(y);
	}
	return sum[x];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		Add(x,y);
		cd[x]++;
		rd[y]++;
	}
	for(int i=1;i<=n;i++){
		if(!rd[i])ans+=DFS(i);
	}
	printf("%d",ans);
	return 0;
}