/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<bitset>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define Bitset bitset<N>
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int M=2005;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
Bitset dis[N];
int n,m,P,cnt,h[N],vis[N],pos[N];
struct edge{int to,next;Bitset data;}d[M];
struct Edge{int x,y,l,r;Bitset data;}e[M];
void Add(int x,int y,Bitset z){
	d[++cnt]=(edge){y,h[x],z};
	h[x]=cnt;
}
Bitset Get(){
	Bitset x;
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int j=1;j<=len;j++){
		x[j]=s[len-j+1]-'0';
	}
	return x;
}
void Print(Bitset x){
	int flag=0;
	for(int i=N-1;i>=1;i--){
		flag|=x[i];
		if(flag)putchar(x[i]+'0');
	}
	if(!flag)putchar('0');
	putchar('\n');
}
struct Node{
	Bitset a[N];
	void Insert(Bitset x){
		for(int i=N-1;i>=1;i--){
			if(x[i]){
				if(!a[i][i]){a[i]=x;return;}
				else x^=a[i];
			}
		}
	}
	Bitset Ask(){
		Bitset ans;
		for(int i=N-1;i>=1;i--){
			if(!ans[i])ans^=a[i];
		}
		return ans;
	}
	void Update(int id){
		Insert(dis[e[id].x]^dis[e[id].y]^e[id].data);
	}
}Basis;
struct Segment_Tree{
	vector<int>G[N*4];
	void Insert(int x,int y,int id,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){G[p].push_back(id);return;}
		int mid=(l+r)>>1;
		Insert(x,y,id,lson);Insert(x,y,id,rson);
	}
	void Query(Node F,int p,int l,int r){
		for(auto id:G[p])F.Update(id);
		if(l==r){Print(F.Ask());return;}
		int mid=(l+r)>>1;
		Query(F,lson);Query(F,rson);
	}
}tree;
void DFS(int x){
	vis[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		dis[y]=dis[x]^d[i].data;
		DFS(y);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();P=read()+1;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		e[i]=(Edge){x,y,1,P,Get()};
		Add(e[i].x,e[i].y,e[i].data);
		Add(e[i].y,e[i].x,e[i].data);
	}
	DFS(1);
	int tot=0;
	for(int i=2;i<=P;i++){
		scanf("%s",s+1);
		if(s[1]=='A'){//Add
			int x=read(),y=read();
			e[++m]=(Edge){x,y,i,P,Get()};
			pos[++tot]=m;
		}
		else if(s[2]=='a'){//Cancel
			int id=read();e[pos[id]].r=i-1;pos[id]=0;
		}
		else{//Change
			int id=read();e[pos[id]].r=i-1;
			e[++m]=(Edge){e[pos[id]].x,e[pos[id]].y,i,P,Get()};
			pos[id]=m;
		}
	}
	for(int i=1;i<=m;i++)tree.Insert(e[i].l,e[i].r,i,1,1,P);
	tree.Query(Basis,1,1,P);
	return 0;
}