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
const int N=2e6+5;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N],t[N];
map<ull,bool>Vis;
ull Hash[N],P[N];
ull GetHash(int l,int r){return Hash[r]-Hash[l-1]*P[r-l+1];}
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int fa[N],len[N],sum[N],ch[N][M];
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				memcpy(ch[fy],ch[y],sizeof(ch[fy]));
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;sum[lst]=1;
	}
	void DFS(int x){for(auto y:G[x]){DFS(y);sum[x]+=sum[y];}}
	void Build(){for(int i=2;i<=tot;i++)G[fa[i]].push_back(i);DFS(1);}
	ll Query(){
		ll ans=0;
		Vis.clear();
		int p=root,d=0;
		for(int i=1;i<m*2;i++){
			int x=t[i]-'a';
			while(p&&!ch[p][x]){p=fa[p];d=len[p];}
			if(p){p=ch[p][x];d++;}else{p=root;d=0;}
			while(d>m&&len[fa[p]]>=m){p=fa[p];d=len[p];}
			if(i>=m&&d>=m){
				ull hash=GetHash(i-m+1,i);
				if(!Vis[hash])ans+=sum[p];
				Vis[hash]=1;
			}
		}
		return ans;
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)sam.Insert(s[i]-'a');
	P[0]=1;for(int i=1;i<N;i++)P[i]=P[i-1]*Mul;
	sam.Build();
	int T=read();
	while(T--){
		scanf("%s",t+1);m=strlen(t+1);
		for(int i=1;i<=m;i++)t[i+m]=t[i];
		for(int i=1;i<=m*2;i++)Hash[i]=Hash[i-1]*Mul+t[i];
		printf("%lld\n",sam.Query());
	}
	return 0;
}
