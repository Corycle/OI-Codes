/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int Mod=998244353;
const ll INF=1e18;
const int N=3e5+5;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
ll Ans[N];
bool vis[N];
vector<int>F[N];
struct edge{int to,next;}d[N];
int n,m,R,tot,top,qnt,cnt,Min,Root;
int a[N],b[N],h[N],t[N],t1[N],fa[N],dep[N],sum[N];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
struct Point{
	int x,y;
	inline double Alpha(){return (!x?1e30:1.0*y/x);}
	friend Point operator-(Point A,Point B){return (Point){A.x-B.x,A.y-B.y};}
	friend Point operator+(Point A,Point B){return (Point){A.x+B.x,A.y+B.y};}
	friend ll operator*(Point A,Point B){return 1ll*A.x*B.x+1ll*A.y*B.y;}
	friend ll operator^(Point A,Point B){return 1ll*A.x*B.y-1ll*A.y*B.x;}
	friend bool operator<(Point A,Point B){return A.x<B.x||(A.x==B.x&&A.y<B.y);}
}P[N],A[N],A1[N];
struct Node{int x,id;Point A;}Q[N];
inline ll Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
inline bool cmp(int x,int y){return Q[x].A.Alpha()>Q[y].A.Alpha();}
inline double Slope(Point A,Point B){return A.x==B.x?1e30:1.0*(A.y-B.y)/(A.x-B.x);}
inline void Insert(int l,Point P){while(top-l+1>=2&&Cross(A[top-1],A[top],P)>=0)top--;A[++top]=P;}
inline void Collect(int x){for(auto tmp:F[x])if(dep[Q[tmp].x]<=R)a[++a[0]]=tmp;}
void dfs(int x){Collect(x);for(int i=h[x];i;i=d[i].next){int y=d[i].to;if(!vis[y])dfs(y);}}
void Find(int x,int num){
	int S=0;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(vis[y])continue;
		Find(y,num);
		sum[x]+=sum[y];
		S=max(S,sum[y]);
	}
	S=max(S,num-sum[x]);
	if(S<=Min){Min=S;Root=x;}
}
int Calc(int ql,int qr,int l,int r){
	if(l==r){
		A[l]=P[b[l]];if(ql<=qr)sort(a+ql,a+qr+1,cmp);
		for(int i=ql;i<=qr;i++)Ans[Q[a[i]].id]=max(Ans[Q[a[i]].id],Q[a[i]].A^A[l]);
		return l;
	}
	int mid=(l+r)>>1;
	int p1=0,p2=0;
	for(int i=ql;i<=qr;i++){
		if(dep[Q[a[i]].x]>=dep[b[mid]]){p1++;a[ql+p1-1]=a[i];}
		else t1[++p2]=a[i];
	}
	int qmid=ql+p1-1;
	for(int i=1;i<=p2;i++)a[qmid+i]=t1[i];
	int n1=Calc(ql,qmid,l,mid);
	int n2=Calc(qmid+1,qr,mid+1,r);
	
	int L=l,R=n1;
	for(int i=qmid+1;i<=qr;i++){
		while(L<R&&Q[a[i]].A.Alpha()<Slope(A[L],A[L+1]))L++;
		if(L<=R)Ans[Q[a[i]].id]=max(Ans[Q[a[i]].id],Q[a[i]].A^A[L]);
	}
	
	int pos=ql;p1=ql;p2=qmid+1;
	while(p1<=qmid&&p2<=qr){
		if(Q[a[p1]].A.Alpha()>Q[a[p2]].A.Alpha())t[pos++]=a[p1++];
		else t[pos++]=a[p2++];
	}
	while(p1<=qmid)t[pos++]=a[p1++];
	while(p2<=qr)t[pos++]=a[p2++];
	for(int i=ql;i<=qr;i++)a[i]=t[i];
	
	for(int i=l;i<=r;i++)A1[i]=A[i];
	top=l-1;p1=l;p2=mid+1;
	while(p1<=n1&&p2<=n2){
		if(A1[p1]<A1[p2])Insert(l,A1[p1++]);
		else Insert(l,A1[p2++]);
	}
	while(p1<=n1)Insert(l,A1[p1++]);
	while(p2<=n2)Insert(l,A1[p2++]);
	return top;
}
void Divide(int x,int num){
	Min=inf;Root=0;Find(x,num);
	int rt=Root,tmp=Root;R=dep[rt];a[0]=b[0]=0;
	while(tmp!=fa[x]){b[++b[0]]=tmp;tmp=fa[tmp];}
	dfs(rt);if(a[0])Calc(1,a[0],1,b[0]);
	for(int i=h[rt];i;i=d[i].next){int y=d[i].to;if(!vis[y])num-=sum[y];}
	for(int i=h[rt];i;i=d[i].next){int y=d[i].to;if(!vis[y]){vis[y]=1;Divide(y,sum[y]);}}
	if(num!=1)Divide(x,num);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();
	while(1){
		n=read();
		if(!n)break;
		top=qnt=cnt=0;tot=1;
		dep[t[top]=tot]=0;
		for(int i=1;i<=n;i++){
			int op=read();
			if(op==1){
				int x=read(),y=read();
				t[++top]=++tot;
				fa[tot]=t[top-1];
				P[tot]=(Point){x,y};
				dep[tot]=dep[t[top-1]]+1;
				Add(t[top-1],tot);
			}
			if(op==2)top--;
			if(op==3){//(x,y) => (-y,x)
				int l=read(),r=read(),x=read(),y=read();
				F[t[r]].push_back(++qnt);Ans[qnt]=-INF;
				Q[qnt]=(Node){t[l],qnt,(Point){x,y}};
			}
		}
		int Answer=0;
		Divide(1,tot);
		for(int i=1;i<=qnt;i++)Answer^=((Ans[i]%Mod+Mod)%Mod);
		printf("%d\n",Answer);
		for(int i=1;i<=tot;i++){
			h[i]=fa[i]=dep[i]=vis[i]=0;
			F[i].clear();
		}
	}
	return 0;
}
