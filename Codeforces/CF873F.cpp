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
const int N=400005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N],a[N];
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int ch[N][M],fa[N],len[N],sum[N];
	void Insert(int num,int id){
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
		lst=fx;sum[fx]='1'-a[id];
	}
	void DFS(int x){for(auto y:G[x]){DFS(y);sum[x]+=sum[y];}}
	void Build(){for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);DFS(root);}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s%s",s+1,a+1);
	for(int i=1;i<=n;i++)sam.Insert(s[i]-'a',i);
	sam.Build();
	ll Ans=0;
	for(int i=1;i<=sam.tot;i++){
		Ans=max(Ans,1ll*sam.len[i]*sam.sum[i]);
	}
	printf("%lld",Ans);
	return 0;
}
