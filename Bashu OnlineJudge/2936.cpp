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
const int M=26;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
vector<int>G[N];
int n,m,Min,Root;
int a[N],vis[N],pos1[N],pos2[N];
struct SAM{
	int tot,lst,root,A[N],B[N];
	int R[N],sum[N],len[N],ch[N][M];
	int s[N],fa[N],num[N],son[N][M];
	inline void Prepare(){tot=lst=root=1;}
	inline void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				memcpy(ch[fy],ch[y],sizeof(ch[y]));
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;sum[fx]=1;R[fx]=len[fx];
	}
	void Calc(int x,int Fa,int p,int Len){
		if(len[p]==Len)p=son[p][a[x]];
		else if(s[R[p]-Len]!=a[x])p=0;
		if(!p)return;num[p]++;
		for(auto y:G[x]){
			if(y==Fa||vis[y])continue;
			Calc(y,x,p,Len+1);
		}
	}
	inline void Clear(){for(int i=1;i<=tot;i++)num[i]=0;}
	inline void Pushup(){
		for(int i=2;i<=tot;i++)num[A[i]]+=num[fa[A[i]]];
	}
	inline void Build(){
		for(int i=1;i<=tot;i++)B[len[i]]++;
		for(int i=1;i<=tot;i++)B[i]+=B[i-1];
		for(int i=tot;i>=1;i--)A[B[len[i]]--]=i;
		for(int i=tot;i>=2;i--){
			int x=A[i];
			sum[fa[x]]+=sum[x];
			R[fa[x]]=max(R[fa[x]],R[x]);
			son[fa[x]][s[R[x]-len[fa[x]]]]=x;
		}
	}
}SAM1,SAM2;

char s1[N],s2[N];
int s[N],p[N],sum[N];
void dfs(int x,int Fa){
	sum[x]=1;
	for(auto y:G[x]){
		if(y==Fa||vis[y])continue;
		dfs(y,x);sum[x]+=sum[y];
	}
}
void DFS1(int x,int Fa){
	p[++p[0]]=x;
	for(auto y:G[x]){
		if(y==Fa||vis[y])continue;
		DFS1(y,x);
	}
}
void DFS2(int x,int Fa,int p){//type 1
	p=SAM1.ch[p][a[x]];
	if(!p)return;
	Ans+=SAM1.sum[p];
	for(auto y:G[x]){
		if(y==Fa||vis[y])continue;
		DFS2(y,x,p);
	}
}
inline void Calc(int x,int Fa,int f){//type 2
	SAM1.Clear();SAM2.Clear();
	if(Fa){
		SAM1.Calc(x,0,SAM1.son[1][a[Fa]],1);
		SAM2.Calc(x,0,SAM2.son[1][a[Fa]],1);
	}
	else{SAM1.Calc(x,0,1,0);SAM2.Calc(x,0,1,0);}
	SAM1.Pushup();SAM2.Pushup();
	for(int i=1;i<=m;i++){
		Ans+=1ll*f*SAM1.num[pos1[i]]*SAM2.num[pos2[m-i+1]];
	}
}
void Find(int x,int Fa,int num){
	int S=0;sum[x]=1;
	for(auto y:G[x]){
		if(y==Fa||vis[y])continue;
		Find(y,x,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<Min){Min=S;Root=x;}
}
void Divide(int x,int num){
	if(1ll*num*num<=m){
		p[0]=0;DFS1(x,0);
		for(int i=1;i<=p[0];i++)DFS2(p[i],0,1);
		return;
	}
	Min=inf;Root=0;Find(x,0,num);
	x=Root;vis[x]=1;Calc(x,0,1);
	dfs(x,0);
	for(auto y:G[x]){
		if(vis[y])continue;
		Calc(y,x,-1);
		Divide(y,sum[y]);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	scanf("%s%s",s1+1,s2+1);
	SAM1.Prepare();SAM2.Prepare();
	for(int i=1;i<=n;i++)a[i]=s1[i]-'a';
	for(int i=1;i<=m;i++)s[i]=s2[i]-'a';
	for(int i=1;i<=m;i++){SAM1.Insert(s[i]);pos1[i]=SAM1.lst;SAM1.s[i]=s[i];}
	reverse(s+1,s+m+1);
	for(int i=1;i<=m;i++){SAM2.Insert(s[i]);pos2[i]=SAM2.lst;SAM2.s[i]=s[i];}
	SAM1.Build();SAM2.Build();Divide(1,n);
	printf("%lld",Ans);
	return 0;
}