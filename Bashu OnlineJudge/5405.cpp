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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,cnt,tot,Min,Root;
int a[N],id[N],sum[N],Sum[N],Ans[N];
bool cmp(int x,int y){return sum[x]>sum[y];}
void Find(int x,int fa){
	int Max=0;sum[x]=1;
	for(auto y:G[x])if(y!=fa){Find(y,x);sum[x]+=sum[y];Max=max(Max,sum[y]);}
	Max=max(Max,n-sum[x]);
	if(Max<Min){Min=Max;Root=x;}
}
void dfs(int x,int fa){sum[x]=1;for(auto y:G[x])if(y!=fa){dfs(y,x);sum[x]+=sum[y];}}
void DFS(int x,int fa,int pre){
	for(auto y:G[x])if(y!=fa)DFS(y,x,pre);
	int num=n-sum[x];
	if(num<=n/2)return;
	if(n-sum[pre]<=n/2)Ans[x]=(x!=pre);
	else if(num-Sum[id[pre]-1]<=n/2){
		int l=1,r=id[pre]-1,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(num-Sum[mid]<=n/2||(n-sum[pre])-Sum[mid-1]<=n/2){ans=mid;r=mid-1;}
			else l=mid+1;
		}
		Ans[x]=ans;
	}
	else{
		int l=id[pre]+1,r=tot,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(num-(Sum[mid]-sum[pre])<=n/2||(n-sum[pre])-(Sum[mid-1]-sum[pre])<=n/2){ans=mid;r=mid-1;}
			else l=mid+1;
		}
		Ans[x]=ans-1;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Min=inf;
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	Find(1,0);dfs(Root,0);
	for(auto x:G[Root])a[++tot]=x;sort(a+1,a+tot+1,cmp);
	for(int i=1;i<=tot;i++){id[a[i]]=i;Sum[i]=Sum[i-1]+sum[a[i]];}
	for(auto x:G[Root])DFS(x,Root,x);
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}