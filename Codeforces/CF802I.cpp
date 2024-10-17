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
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m;
char s[N];
struct SAM{
	vector<int>G[N];
	int tot,lst,root;
	int fa[N],len[N],sum[N],ch[N][M];
	void Init(){
		for(int i=1;i<=tot;i++){
			for(int j=0;j<M;j++)ch[i][j]=0;
			fa[i]=len[i]=sum[i]=0;G[i].clear();
		}
		tot=lst=root=1;
	}
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
		lst=fx;sum[fx]=1;
	}
	void DFS(int x){for(auto y:G[x]){DFS(y);sum[x]+=sum[y];}Ans+=1ll*(len[x]-len[fa[x]])*sum[x]*sum[x];}
	void Solve(){for(int i=2;i<=tot;i++)G[fa[i]].push_back(i);DFS(root);}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int Case=read();
	while(Case--){
		scanf("%s",s+1);n=strlen(s+1);sam.Init();
		for(int i=1;i<=n;i++)sam.Insert(s[i]-'a');
		Ans=0;sam.Solve();printf("%lld\n",Ans);
	}
	return 0;
}
