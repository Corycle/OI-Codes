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
const int N=1000005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,K,type;
struct SAM{
	vector<int>G[N];
	int tot=1,lst=1,root=1;
	int ch[N][M],fa[N],sum[N],len[N],vis[N],f[N];
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
	void DFS(int x){for(auto y:G[x]){DFS(y);sum[x]+=sum[y];}}
	void Calc(int x){
		if(vis[x])return;
		f[x]=sum[x];vis[x]=1;
		for(int i=0;i<26;i++){
			if(!ch[x][i])continue;
			Calc(ch[x][i]);
			f[x]+=f[ch[x][i]];
		}
	}
	void Build(){
		for(int i=1;i<=n;i++)Insert(s[i]-'a');
		for(int i=1;i<=tot;i++)G[fa[i]].push_back(i);
		if(type==0)for(int i=1;i<=tot;i++)sum[i]=1;
		else DFS(root);
		sum[root]=0;
		Calc(root);
	}
	void Query(){
		int p=root;
		if(f[p]<K){printf("-1");return;}
		while(K>sum[p]){
			K-=sum[p];
			for(int i=0;i<26;i++){
				if(K>f[ch[p][i]])K-=f[ch[p][i]];
				else{printf("%c",'a'+i);p=ch[p][i];break;}
			}
		}
	}
}sam;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	type=read();K=read();
	sam.Build();sam.Query();
	return 0;
}