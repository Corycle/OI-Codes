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
const int N=30005;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N][M];
int n,deg[M],Ans[N];
struct Tree{int ch[26],tag;};
struct Trie{
	int tot=1;
	Tree t[N*M];
	vector<int>G[M];
	void Insert(int id){
		int p=1,len=strlen(s[id]+1);
		for(int i=1;i<=len;i++){
			int x=s[id][i]-'a';
			if(!t[p].ch[x])t[p].ch[x]=++tot;
			p=t[p].ch[x];
		}
		t[p].tag=1;
	}
	void Add(int x,int y){G[x].push_back(y);deg[y]++;}
	bool Solve(){
		queue<int>q;
		for(int i=0;i<26;i++)if(!deg[i])q.push(i);
		while(q.size()){
			int x=q.front();q.pop();
			for(auto y:G[x]){
				deg[y]--;
				if(!deg[y])q.push(y);
			}
		}
		for(int i=0;i<26;i++)if(deg[i])return false;
		return true;
	}
	bool Check(int id){
		int p=1,len=strlen(s[id]+1);
		for(int i=0;i<26;i++){deg[i]=0;G[i].clear();}
		for(int i=1;i<=len;i++){
			int x=s[id][i]-'a';
			if(t[p].tag)return false;
			for(int y=0;y<26;y++){
				if(x!=y&&t[p].ch[y])Add(x,y);
			}
			p=t[p].ch[x];
		}
		return Solve();
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){scanf("%s",s[i]+1);tree.Insert(i);}
	for(int i=1;i<=n;i++)if(tree.Check(i))Ans[++Ans[0]]=i;
	printf("%d\n",Ans[0]);
	for(int i=1;i<=Ans[0];i++)printf("%s\n",s[Ans[i]]+1);
	return 0;
}