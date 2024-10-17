#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s1=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s1=s1*10+c-'0';c=getchar();}
	return s1*f;
}
char a[N][10];
int n,m,fa[N];
int num[N],cnt[N],Flag[N];
struct Tree{
	int sum;
	int s1[10],s2[10];
	bool f2[10],f1[10];//联通块内是否有建筑 
	void Init(){
		sum=0;
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		memset(f2,0,sizeof(f2));
		memset(f1,0,sizeof(f1));
	}
}t[N*4];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
bool Check(char a,char b,char c){//a,b是否联通 
	return (a=='O'||a==c||a=='+')&&(b=='O'||b==c||b=='+');
}
void Reset(int p,int x){
	t[p].Init();
	int scc=0,j=0;
	for(int i=1;i<=m;i=j+1){
		int flag=0;j=i;scc++;
		if(a[x][i]=='.')continue;
		while(j<m&&Check(a[x][j],a[x][j+1],'-'))j++;
		for(int k=i;k<=j&&!flag;k++)flag=(a[x][k]=='O');
		//flag表示联通块内有没有建筑 
		for(int k=i;k<=j;k++){
			t[p].s1[k]=t[p].s2[k]=scc;
			t[p].f2[k]=t[p].f1[k]=flag;
		}
		t[p].sum+=flag;
	}
}
void Pushup(Tree &x,Tree L,Tree R,int l,int r,int mid){
	int scc=0;x.Init();x.sum=L.sum+R.sum;
	for(int i=1;i<=m*4;i++){fa[i]=i;cnt[i]=num[i]=0;}
	for(int i=1;i<=m;i++){
		if(L.s1[i])cnt[L.s1[i]]=L.f1[i];
		if(R.s2[i])cnt[R.s2[i]+2*m]=R.f2[i];
		if(L.s2[i]){cnt[L.s2[i]]=L.f2[i];Flag[L.s2[i]]=1;}
		if(R.s1[i]){cnt[R.s1[i]+2*m]=R.f1[i];Flag[R.s1[i]+2*m]=1;}
	}
	for(int i=1;i<=m;i++){
		if(!Check(a[mid][i],a[mid+1][i],'|'))continue;
		int fx=Find(L.s2[i]);
		int fy=Find(R.s1[i]+2*m);
		if(fx==fy)continue;
		fa[fy]=fx;cnt[fx]+=cnt[fy];
	}
	for(int i=1;i<=m*4;i++){
		if(fa[i]==i&&Flag[i]&&cnt[i])x.sum-=cnt[i]-1;
	}
	for(int i=1;i<=m;i++){
		if(L.s1[i]){
			int fx=Find(L.s1[i]);
			if(!num[fx])num[fx]=++scc;
			x.s1[i]=num[fx];
			x.f1[i]=cnt[fx];
		}
		if(R.s2[i]){
			int fx=Find(R.s2[i]+2*m);
			if(!num[fx])num[fx]=++scc;
			x.s2[i]=num[fx];
			x.f2[i]=cnt[fx];
		}
	}
}
void Build(int p,int l,int r){
	if(l==r){Reset(p,l);return;}
	int mid=(l+r)>>1;
	Build(lson);Build(rson);
	Pushup(t[p],t[p<<1],t[p<<1|1],l,r,mid);
}
void Change(int x,int p,int l,int r){
	if(x<l||x>r)return;
	if(l==r){Reset(p,l);return;}
	int mid=(l+r)>>1;
	Change(x,lson);Change(x,rson);
	Pushup(t[p],t[p<<1],t[p<<1|1],l,r,mid);
}
Tree Ask(int x,int y,int p,int l,int r){
	if(y<l||x>r)return (Tree){0};
	if(x<=l&&r<=y)return t[p];
	int mid=(l+r)>>1;
	Tree L=Ask(x,y,lson);
	Tree R=Ask(x,y,rson);
	if(y<=mid)return L;
	if(x>mid)return R;
	Tree ans;
	Pushup(ans,L,R,x,y,mid);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]+1);
	}
	Build(1,1,n);
	int Q=read();
	while(Q--){
		char op[5],ch[5];
		scanf("%s",op);
		int x=read(),y=read();
		if(op[0]=='C'){
			scanf("%s",ch);
			a[x][y]=ch[0];
			Change(x,1,1,n);
		}
		if(op[0]=='Q'){
			Tree ans=Ask(x,y,1,1,n);
			printf("%d\n",ans.sum);
		}
	}
	return 0;
}