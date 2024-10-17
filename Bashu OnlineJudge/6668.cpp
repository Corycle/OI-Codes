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
#define re register
#define ll long long
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=131073;
const int M=52;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char T[M][M],S[N],tmp[N];
int ch[M][26],fail[N],sum[N];
int n,m,tot,num,Lim,Ans,Pos;
struct Trie{
	int tot,Root;
	void Init(){tot=Root=1;}
	void Insert(int id){
		int p=1,len=strlen(T[id]+1);
		for(int i=1;i<=len;i++){
			int x=T[id][i]-'a';
			if(!ch[p][x])ch[p][x]=++tot;
			p=ch[p][x];
		}
		sum[p]++;
	}
	void Build(){
		queue<int>q;fail[1]=1;
		for(int i=0;i<26;i++){
			if(!ch[1][i])ch[1][i]=1;
			else{fail[ch[1][i]]=1;q.push(ch[1][i]);}
		}
		while(q.size()){
			int x=q.front();q.pop();
			sum[x]+=sum[fail[x]];
			for(int i=0;i<26;i++){
				if(!ch[x][i])ch[x][i]=ch[fail[x]][i];
				else{fail[ch[x][i]]=ch[fail[x]][i];q.push(ch[x][i]);}
			}
		}
	}
}tree;
/*========Thanks For CHY's Code========*/
int Num,Lg[N],tl[N],len[N<<2],lc[N<<2],rc[N<<2],d[N<<2];
struct Node{
	int p[M],f[M];
	inline friend Node operator+(Node A,Node B){
		for(re int x=1;x<=tree.tot;++x){
			A.f[x]=A.f[x]+B.f[A.p[x]];
			A.p[x]=B.p[A.p[x]];
		}return A;
	}
}tr[N<<1];
struct Info{
	vector<Node> H[17];
	void Init(char *S){
		int n=strlen(S+1);
		for(re int j=0;j<=16;++j)H[j].resize(n+1);
		for(re int i=1;i<=n;++i){
			int c=S[i]-'a';
			for(re int x=1;x<=tree.tot;x++){
				H[0][i].p[x]=ch[x][c];
				H[0][i].f[x]=sum[ch[x][c]];
			}
		}
		for(re int j=1;j<=16;++j)
		for(re int i=1;i<=n;++i)
		for(re int x=1;x<=tree.tot;++x){
			int y=H[j-1][i].p[x],t=(i+(1<<(j-1))-1)%n+1;
			H[j][i].p[x]=H[j-1][t].p[y];
			H[j][i].f[x]=H[j-1][i].f[x]+H[j-1][t].f[y];
		}
	}
};vector<Info> G;
struct Segment_Tree{
	inline void Pushup(int x){tr[x]=tr[x<<1]+tr[x<<1|1];}
	inline void Init(int x,int id){
		int j=Lg[rc[x]-lc[x]+1];
		int i=(lc[x]-tl[id])%len[id]+1;
		d[x]=id,tr[x]=G[id].H[j][i];
	}
	void Pushdown(int x){
		if(!d[x])return;
		Init(x<<1,d[x]),Init(x<<1|1,d[x]),d[x]=0;
	}
	void Build(int x,int l,int r){
		lc[x]=l,rc[x]=r;if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);if(mid+1<=n)Build(rson);
	}
	void Ins(int x,int l,int r,int ql,int qr,int t){
		if(ql<=l&&r<=qr)return Init(x,t);
		int mid=(l+r)>>1;Pushdown(x);
		if(ql<=mid)Ins(lson,ql,qr,t);
		if(qr>mid)Ins(rson,ql,qr,t);if(r<=n)Pushup(x);
	}
	Node Ask(int x,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return tr[x];
		int mid=(l+r)>>1;Pushdown(x);
		if(qr<=mid)return Ask(lson,ql,qr);
		if(ql>mid)return Ask(rson,ql,qr);
		return Ask(lson,ql,qr)+Ask(rson,ql,qr);
	}
}sgt;
void Upd(int l,int r,char *S){
	len[++Num]=strlen(S+1),tl[Num]=l;
	G.resize(Num+1),G[Num].Init(S);sgt.Ins(1,1,Lim,l,r,Num);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();tree.Init();
	for(int i=1;i<=n;i++){scanf("%s",T[i]+1);tree.Insert(i);}
	tree.Build(),scanf("%s",S+1),n=strlen(S+1);
	for(Lim=1;Lim<n;Lim<<=1);
	for(int i=2;i<=Lim;i++)Lg[i]=Lg[i>>1]+1;
	sgt.Build(1,1,Lim);Upd(1,n,S);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){scanf("%s",S+1);Upd(l,r,S);}
		if(op==2){printf("%d\n",sgt.Ask(1,1,Lim,l,r).f[1]);}
	}
	return 0;
}