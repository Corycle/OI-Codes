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
const int Mod1=1e9+7;
const int Mod2=1e9+9;
const int Mul1=13131;
const int Mul2=131;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,cnt,tot;
int h[N],fa[N],id[N],pos[N],sum[N],dep[N],son[N],top[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){d[++cnt]=(edge){y,h[x]};h[x]=cnt;}
int mod1(int x){return x>=Mod1?x-Mod1:x;}
int mod2(int x){return x>=Mod2?x-Mod2:x;}
struct Node{int x,y;};
struct Hash{
	int h1,h2;
	friend Hash operator+(Hash A,Hash B){return (Hash){mod1(A.h1+B.h1),mod2(A.h2+B.h2)};}
	friend Hash operator-(Hash A,Hash B){return (Hash){mod1(A.h1-B.h1+Mod1),mod2(A.h2-B.h2+Mod2)};}
	friend Hash operator*(Hash A,Hash B){return (Hash){(int)(1ll*A.h1*B.h1%Mod1),(int)(1ll*A.h2*B.h2%Mod2)};}
}H1[N],H2[N],P[N],Mul;
Hash GetHash(bool flag,int x,int len){return flag?(H1[x+len-1]-H1[x-1]*P[len]):(H2[x-len+1]-H2[x+1]*P[len]);}
void DFS1(int x,int depth){
	dep[x]=depth;sum[x]=1;
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;fa[y]=x;
		DFS1(y,depth+1);sum[x]+=sum[y];
		if(sum[son[x]]<sum[y])son[x]=y;
	}
}
void DFS2(int x,int tp){
	top[x]=tp;pos[id[x]=++tot]=x;
	if(son[x])DFS2(son[x],tp);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==son[x]||y==fa[x])continue;
		DFS2(y,y);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	return dep[x]<dep[y]?x:y;
}
vector<Node> GetPath(int x,int y){
	int z=LCA(x,y);vector<Node>f1,f2;
	while(dep[top[x]]>dep[z]){f1.push_back((Node){x,top[x]});x=fa[top[x]];}f1.push_back((Node){x,z});
	while(dep[top[y]]>dep[z]){f2.push_back((Node){top[y],y});y=fa[top[y]];}if(y!=z)f2.push_back((Node){son[x],y});
	while(f2.size()){f1.push_back(f2.back());f2.pop_back();}
	return f1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s",s+1);
	P[0]=(Hash){1,1};
	Mul=(Hash){Mul1,Mul2};
	for(int i=1;i<=n;i++)P[i]=P[i-1]*Mul;
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		Add(x,y);Add(y,x);
	}
	DFS1(1,1);DFS2(1,1);
	for(int i=1;i<=n;i++)H1[i]=H1[i-1]*Mul+(Hash){s[pos[i]],s[pos[i]]};
	for(int i=n;i>=1;i--)H2[i]=H2[i+1]*Mul+(Hash){s[pos[i]],s[pos[i]]};
	m=read();
	while(m--){
		int Ans=0,s=0,t=0;
		int sx=read(),sy=read();
		int tx=read(),ty=read();
		vector<Node>F1=GetPath(sx,sy);
		vector<Node>F2=GetPath(tx,ty);
		while(s<F1.size()&&t<F2.size()){
			int s1=id[F1[s].x],s2=id[F1[s].y],len1=abs(s1-s2)+1;
			int t1=id[F2[t].x],t2=id[F2[t].y],len2=abs(t1-t2)+1;
			bool flag1=s1<s2,flag2=t1<t2;
			int len=min(len1,len2);
			Hash f1=GetHash(flag1,s1,len);
			Hash f2=GetHash(flag2,t1,len);
			if(f1.h1==f2.h1&&f1.h2==f2.h2){
				Ans+=len;
				if(len==len1)s++;else F1[s].x=pos[s1+(flag1?1:-1)*len];
				if(len==len2)t++;else F2[t].x=pos[t1+(flag2?1:-1)*len];
			}
			else{
				int l=1,r=len,ans=0;
				while(l<=r){
					int mid=(l+r)>>1;
					f1=GetHash(flag1,s1,mid);
					f2=GetHash(flag2,t1,mid);
					if(f1.h1==f2.h1&&f1.h2==f2.h2){ans=mid;l=mid+1;}
					else r=mid-1;
				}
				Ans+=ans;
				break;
			}
		}
		printf("%d\n",Ans);
	}                               
	return 0;
}
