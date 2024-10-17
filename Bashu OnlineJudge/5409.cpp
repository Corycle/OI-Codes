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
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int Mul=13131;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,m,cnt,Max,Min,Root;
ull a[N],P[N],Hash1[N],Hash2[N];
int h[N],s1[N],s2[N],vis[N],sum[N];
int sum1[N],sum2[N],tmp1[N],tmp2[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Find(int x,int fa,int num){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void DFS(int x,int fa,int depth,int Mid,ull Hash){
	Max=max(Max,depth%m);Hash+=a[x]*P[depth-1];
	if(Hash==Hash1[depth]){tmp1[depth%m]++;if(Mid==s1[depth+1])Ans+=sum2[m-depth%m-1];}
	if(Hash==Hash2[depth]){tmp2[depth%m]++;if(Mid==s2[depth+1])Ans+=sum1[m-depth%m-1];}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa||vis[y])continue;
		DFS(y,x,depth+1,Mid,Hash);
	}
}
void Calc(int x){
	Max=0;
	if(a[x]==Hash1[1])sum1[0]++;
	if(a[x]==Hash2[1])sum2[0]++;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		DFS(y,x,1,a[x],0);
		for(int j=0;j<=Max;j++){
			sum1[j]+=tmp1[j];tmp1[j]=0;
			sum2[j]+=tmp2[j];tmp2[j]=0;
		}
	}
	for(int i=0;i<=Max;i++)sum1[i]=sum2[i]=0;
}
void Divide(int x,int num){
	if(num<m)return;
	Min=inf;Root=0;Find(x,0,num);
	x=Root;vis[x]=1;Calc(x);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Divide(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	P[0]=1;
	for(int i=1;i<N;i++)P[i]=P[i-1]*Mul;
	int Case=read();
	while(Case--){
		n=read();m=read();scanf("%s",s+1);
		for(int i=1;i<=n;i++)a[i]=s[i]-'A';
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			Add(x,y);Add(y,x);
		}
		scanf("%s",s+1);
		for(int i=1;i<=m;i++)s1[i]=s2[m-i+1]=s[i]-'A';
		for(int i=m+1;i<=n;i++){s1[i]=s1[i-m];s2[i]=s2[i-m];}
		for(int i=1;i<=n;i++){
			Hash1[i]=Hash1[i-1]*Mul+s1[i];
			Hash2[i]=Hash2[i-1]*Mul+s2[i];
		}
		Divide(1,n);
		printf("%lld\n",Ans);
		for(int i=1;i<=n;i++)h[i]=vis[i]=0;
		cnt=Ans=0;
	}
	return 0;
}