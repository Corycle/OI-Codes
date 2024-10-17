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
const int Maxn=1e6+5;
const int N=6e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Sum;
struct String{
	int len;
	string s;
	vector<int>nxt;
	void Prepare(){
		nxt.push_back(0);nxt.push_back(0);
		for(int i=2,j=0;i<=len;i++){
			if(j&&s[i]!=s[j+1])j=nxt[j];
			if(s[i]==s[j+1])j++;
			nxt.push_back(j);
		}
	}
}A[N];
namespace Task1{
	const int M=5005;
	int Ans[M][M];
	int Query(String &S,String &T){
		int len=S.len,Ans=0;
		for(int i=1,j=0;i<=len;i++){
			while(j&&S.s[i]!=T.s[j+1])j=T.nxt[j];
			if(S.s[i]==T.s[j+1])j++;Ans=j;
		}
		return Ans;
	}
	void Main(){
		for(int i=1;i<=n;i++)A[i].Prepare();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)Ans[i][j]=Query(A[i],A[j]);
		}
		while(m--){int x=read(),y=read();cout<<Ans[x][y]<<'\n';}
	}
}
namespace Task2{
	int cnt,h[N],pos[N],ans[N],Ans[Maxn];
	struct edge{int to,next;}d[N];
	void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
	struct Node{int x,id;};
	vector<Node>Q[N];
	vector<int>F[N];
	struct Tree{
		int root,tot;
		int ch[N][26],dep[N],fail[N];
		void Init(){root=tot=1;}
		int Insert(int id){
			int p=root,len=A[id].len;
			for(int i=1;i<=len;i++){
				int x=A[id].s[i]-'a';
				if(!ch[p][x])ch[p][x]=++tot;
				p=ch[p][x];dep[p]=i;
				F[p].push_back(id);
			}
			return p;
		}
		void Build(){
			queue<int>q;fail[1]=1;
			for(int i=0;i<26;i++){
				if(!ch[1][i])ch[1][i]=1;
				else {q.push(ch[1][i]);fail[ch[1][i]]=1;}
			}
			while(q.size()){
				int x=q.front();q.pop();
				for(int i=0;i<26;i++){
					if(ch[x][i]){
						q.push(ch[x][i]);
						fail[ch[x][i]]=ch[fail[x]][i];
					}
					else ch[x][i]=ch[fail[x]][i];
				}
			}
			for(int i=2;i<=tot;i++)Add(fail[i],i);
		}
	}tree;
	int st[N],lst[N],top;
	inline void Update(int x,int v){top++;st[top]=x;lst[top]=ans[x];ans[x]=v;}
	inline void Reset(int tmp){while(top>tmp){ans[st[top]]=lst[top];top--;}}
	void DFS(int x){
		int tmp=top;
		for(int i=0,num=F[x].size();i<num;i++)Update(F[x][i],tree.dep[x]);
		for(int i=0,num=Q[x].size();i<num;i++)Ans[Q[x][i].id]=ans[Q[x][i].x];
		for(int i=h[x];i;i=d[i].next)DFS(d[i].to);
		Reset(tmp);
	}
	void Main(){
		tree.Init();
		for(int i=1;i<=n;i++)pos[i]=tree.Insert(i);
		tree.Build();
		for(int i=1;i<=m;i++){int x=read(),y=read();Q[pos[x]].push_back((Node){y,i});}
		DFS(1);
		for(int i=1;i<=m;i++)cout<<Ans[i]<<'\n';
	}
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		A[i].len=strlen(s);
		A[i].s=" "+(string)(s)+" ";
		Sum+=A[i].len;
	}
	if(n<=10||Sum<=5000){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}