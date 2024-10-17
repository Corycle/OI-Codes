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
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N],F[N];
int n,m,Ans,Root,Min;
int b[N],c[N],vis[N],vst[N],Vst[N],pre[N],sum[N],Num[N];
void Find(int x,int fa,int num){
	int S=0;sum[x]=1;
	for(auto y:G[x]){
		if(vis[y]||y==fa)continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void dfs(int x,int fa,int f){
	sum[x]=1;pre[x]=fa;b[c[x]]+=f;vst[c[x]]=0;Vst[x]=0;
	for(auto y:G[x]){
		if(vis[y]||y==fa)continue;
		dfs(y,x,f);sum[x]+=sum[y];
	}
}
bool Insert(int c,queue<int>&q){
	if(b[c]!=Num[c])return false;
	vst[c]=1;for(auto x:F[c])q.push(x);
	return true;
}
void Calc(int x){
	dfs(x,0,1);
	int ans=1;queue<int>q;
	if(!Insert(c[x],q)){dfs(x,0,-1);return;}
	while(q.size()){
		int t=q.front();q.pop();
		while(t){
			if(Vst[t])break;
			Vst[t]=1;
			if(!vst[c[t]]){
				if(!Insert(c[t],q)){dfs(x,0,-1);return;}
				ans++;
			}
			t=pre[t];
		}
	}
	Ans=min(Ans,ans);
	dfs(x,0,-1);
}
void Divide(int x,int num){
	Root=0;Min=inf;Find(x,0,num);x=Root;vis[x]=1;Calc(x);
	for(auto y:G[x])if(!vis[y])Divide(y,sum[y]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Ans=m;
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	for(int i=1;i<=n;i++){c[i]=read();Num[c[i]]++;F[c[i]].push_back(i);}
	Divide(1,n);
	printf("%d",Ans-1);
	return 0;
}