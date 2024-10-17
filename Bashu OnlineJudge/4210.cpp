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
const int N=1e5+5;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,tot;
ll sum[N],Ans[N];
int L[N],R[N],len[N];
vector<int>G[N],Pos[N];
struct Ques{int x,y,id;};
vector<Ques>F[N],Q[N];
struct Tree{
	int tot=1,root=1,ch[N][M],fail[N];
	void Insert(int id){
		int p=root;
		len[id]=strlen(s+1);
		Pos[id].push_back(p);
		for(int i=1;i<=len[id];i++){
			int c=s[i]-'a';
			if(!ch[p][c])ch[p][c]=++tot;
			p=ch[p][c];Pos[id].push_back(p);
		}
	}
	void Build(){
		queue<int>q;fail[root]=root;
		for(int i=0;i<M;i++){
			if(ch[root][i]){
				q.push(ch[root][i]);
				fail[ch[root][i]]=root;
			}
			else ch[root][i]=root;
		}
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<M;i++){
				if(ch[x][i]){
					q.push(ch[x][i]);
					fail[ch[x][i]]=ch[fail[x]][i];
				}
				else ch[x][i]=ch[fail[x]][i];
			}
		}
		for(int i=2;i<=tot;i++)G[fail[i]].push_back(i);
	}
}tree;
struct BIT{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Init(){for(int i=1;i<=tot;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=tot;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	ll Query(int l,int r){return Ask(r)-Ask(l-1);}
}bit;
void DFS(int x){L[x]=++tot;for(auto y:G[x])DFS(y);R[x]=tot;}
void Solve1(int id){
	bit.Init();
	for(int i=1;i<=len[id];i++)bit.Add(L[Pos[id][i]],1);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+bit.Query(L[Pos[i][len[i]]],R[Pos[i][len[i]]]);
	for(auto tmp:F[id])Ans[tmp.id]=sum[tmp.y]-sum[tmp.x-1];
}
void Solve2(){
	bit.Init();
	for(int r=1;r<=n;r++){
		bit.Add(L[Pos[r][len[r]]],1);
		bit.Add(R[Pos[r][len[r]]]+1,-1);
		for(auto tmp:Q[r]){
			for(int i=1;i<=len[tmp.x];i++){
				Ans[tmp.id]+=tmp.y*bit.Ask(L[Pos[tmp.x][i]]);
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		tree.Insert(i);
	}
	tree.Build();DFS(1);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=read();
		if(len[x]>=320)F[x].push_back((Ques){l,r,i});
		else{
			Q[r].push_back((Ques){x,1,i});
			Q[l-1].push_back((Ques){x,-1,i});
		}
	}
	for(int i=1;i<=n;i++)if(!F[i].empty())Solve1(i);
	Solve2();
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}