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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
ll a[N],P[15];
int Pos(ll x){return (lower_bound(P+1,P+11,x)-P);}
void Prepare(){P[0]=1;for(int i=1;i<=10;i++)P[i]=P[i-1]*42;}
struct Tree{ll Min,tag1,tag2;int num;};
struct Segment_Tree{
	Tree t[N*4];
	void update(int p,ll x){
		if(t[p].num){
			t[p].tag1-=x;
			while(t[p].tag1<0){t[p].num++;t[p].tag1+=P[t[p].num]-P[t[p].num-1];}
			t[p].Min=t[p].tag1;
		}
		else{t[p].tag2+=x;t[p].Min-=x;}
	}
	void Init(int p,ll val,int num){t[p]=(Tree){val,val,0,num};}
	void Pushup(int p){t[p].Min=min(t[p<<1].Min,t[p<<1|1].Min);}
	void Pushdown(int p){
		if(t[p].tag1){Init(p<<1,t[p].tag1,t[p].num);Init(p<<1|1,t[p].tag1,t[p].num);t[p].tag1=t[p].num=0;}
		if(t[p].tag2){update(p<<1,t[p].tag2);update(p<<1|1,t[p].tag2);t[p].tag2=0;}
	}
	void Change(int x,int y,ll val,int num,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Init(p,val,num);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Change(x,y,val,num,lson);Change(x,y,val,num,rson);Pushup(p);
	}
	void Update(int x,int y,ll val,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y&&(t[p].Min>=val||t[p].num)){update(p,val);return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,val,lson);Update(x,y,val,rson);Pushup(p);
	}
	ll Query(int x,int p,int l,int r){
		if(l==r)return P[t[p].num]-t[p].tag1;
		int mid=(l+r)>>1;Pushdown(p);
		return (x<=mid?Query(x,lson):Query(x,rson));
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++){
		int pos=Pos(a[i]=read());
		tree.Change(i,i,P[pos]-a[i],pos,1,1,n);
	}
	while(m--){
		int op=read();
		if(op==1)printf("%lld\n",tree.Query(read(),1,1,n));
		if(op==2){
			int l=read(),r=read();ll x=read();int pos=Pos(x);
			tree.Change(l,r,P[pos]-x,pos,1,1,n);
		}
		if(op==3){
			int l=read(),r=read();ll x=read();
			while(1){tree.Update(l,r,x,1,1,n);if(tree.t[1].Min)break;}
		}
	}
	return 0;
}
