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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
int h[N],f[N],Ans[N],sum1[N],sum2[N];
struct edge{int to,next;}d[N];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void Prepare(){
	cnt=Ans[0]=0;
	for(int i=1;i<=n;i++){
		h[i]=f[i]=sum1[i]=sum2[i]=0;
	}
}
void DFS1(int x){
	if(f[x]==0)sum1[x]=1;
	if(f[x]==1)sum2[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS1(y);
		if(f[y]==0)sum1[x]++;
		if(f[y]==1)sum2[x]++;
	}
	if(sum1[x]>sum2[x])f[x]=0;
	if(sum1[x]<sum2[x])f[x]=1;
	if(sum1[x]==sum2[x])f[x]=-1;
}
void DFS2(int x){
	if(f[1]==-1&&(f[x]==0||sum1[x]+1<sum2[x]))return;
	if(!h[x]&&f[x]==-1)Ans[++Ans[0]]=x;
	for(int i=h[x];i;i=d[i].next)DFS2(d[i].to);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();Prepare();
		for(int i=1;i<=n;i++)Add(read(),i);
		for(int i=1;i<=n;i++)f[i]=read();
		DFS1(1);
		if(f[1]==1)printf("-1\n");
		else{
			DFS2(1);
			sort(Ans+1,Ans+Ans[0]+1);
			for(int i=0;i<=Ans[0];i++)printf("%d ",Ans[i]);
			printf("\n");
		}
	}
	return 0;
}