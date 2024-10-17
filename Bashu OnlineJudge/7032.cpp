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
const int N=3e5+5;
const int M=22;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,Root[2][N];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	#define lson t[p].l,l,mid
	#define rson t[p].r,mid+1,r
	#define Lson t[px].l,t[py].l,l,mid
	#define Rson t[px].r,t[py].r,mid+1,r
	int tot;
	Tree t[N*M];
	void Update(int x,int &p,int l,int r){
		t[++tot]=t[p];p=tot;t[p].sum++;
		if(l==r)return;int mid=(l+r)>>1;
		x<=mid?Update(x,lson):Update(x,rson);
	}
	int Ask(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return 0;
		if(x<=l&&r<=y)return t[py].sum-t[px].sum;
		int mid=(l+r)>>1;
		return Ask(x,y,Lson)+Ask(x,y,Rson);
	}
	int Ask1(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return -1;
		if(l==r)return l;int mid=(l+r)>>1;
		int tmp=Ask1(x,y,Rson);
		return tmp!=-1?tmp:Ask1(x,y,Lson);
	}
	int Ask2(int x,int y,int px,int py,int l,int r){
		if(y<l||x>r||!(t[py].sum-t[px].sum))return -1;
		if(l==r)return l;int mid=(l+r)>>1;
		int tmp=Ask2(x,y,Lson);
		return tmp!=-1?tmp:Ask2(x,y,Rson);
	}
	#undef lson
	#undef rson
	#undef Lson
	#undef Rson
}t1[2];
struct Segment_Tree2{
	int t[Maxn*4];
	#define lson p<<1,l,mid
	#define rson p<<1|1,mid+1,r
	void Update(int x,int val,int p,int l,int r){
		if(l==r){t[p]=val;return;}int mid=(l+r)>>1;
		x<=mid?Update(x,val,lson):Update(x,val,rson);
		t[p]=min(t[p<<1],t[p<<1|1]);
	}
	int Ask(int x,int y,int p,int l,int r){
		if(y<l||x>r)return inf;
		if(x<=l&&r<=y)return t[p];
		int mid=(l+r)>>1;
		return min(Ask(x,y,lson),Ask(x,y,rson));
	}
	#undef lson
	#undef rson
}t2[2];
int main(){
//	freopen("snow.in","r",stdin);
//	freopen("snow.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=Q;i++){
		int op=read();
		Root[0][i]=Root[0][i-1];Root[1][i]=Root[1][i-1];
		if(op==1){
			int x=read();
			t2[0].Update(x,i,1,1,n);
			t1[0].Update(x,Root[0][i],1,n);
		}
		if(op==2){
			int x=read();
			t2[1].Update(x,i,1,1,m);
			t1[1].Update(x,Root[1][i],1,m);
		}
		if(op==3){
			int sx=read(),sy=read(),tx=read(),ty=read(),k=read();
			if(k>=i){printf("%d\n",abs(sx-tx)+abs(sy-ty));continue;}
			int f1=t1[0].Ask(sx,sx,Root[0][i-k-1],Root[0][i-1],1,n);
			int f2=t1[1].Ask(sy,sy,Root[1][i-k-1],Root[1][i-1],1,m);
			if((sx==tx&&f1)||(sy==ty&&f2)){printf("%d\n",abs(sx-tx)+abs(sy-ty));continue;}
			int f3=t1[0].Ask(tx,tx,Root[0][i-k-1],Root[0][i-1],1,n);
			int f4=t1[1].Ask(ty,ty,Root[1][i-k-1],Root[1][i-1],1,m);
			if((!f1&&!f2)||(!f3&&!f4)){puts("-1");continue;}
			if((f1&&f4)||(f2&&f3)){printf("%d\n",abs(sx-tx)+abs(sy-ty));continue;}
			int Minx=min(sx,tx),Maxx=max(sx,tx),Miny=min(sy,ty),Maxy=max(sy,ty);
			int g1=t1[0].Ask(Minx,Maxx,Root[0][i-k-1],Root[0][i-1],1,n);
			int g2=t1[1].Ask(Miny,Maxy,Root[1][i-k-1],Root[1][i-1],1,m);
			if((f2&&f4&&g1)||t2[0].Ask(Minx,Maxx,1,1,n)>=i-k){printf("%d\n",abs(sx-tx)+abs(sy-ty));continue;}
			if((f1&&f3&&g2)||t2[1].Ask(Miny,Maxy,1,1,m)>=i-k){printf("%d\n",abs(sx-tx)+abs(sy-ty));continue;}
			if(f1&&f3&&!t1[1].Ask(1,m,Root[1][i-k-1],Root[1][i-1],1,m)){puts("-1");continue;}
			if(f2&&f4&&!t1[0].Ask(1,n,Root[0][i-k-1],Root[0][i-1],1,n)){puts("-1");continue;}
			int ans=inf,pos=0;
			if(f1&&f3){
				pos=t1[1].Ask1(1,Miny,Root[1][i-k-1],Root[1][i-1],1,m);if(pos!=-1)ans=min(ans,Miny+Maxy-pos*2+abs(sx-tx));
				pos=t1[1].Ask2(Maxy,m,Root[1][i-k-1],Root[1][i-1],1,m);if(pos!=-1)ans=min(ans,pos*2-Miny-Maxy+abs(sx-tx));
			}
			if(f2&&f4){
				pos=t1[0].Ask1(1,Minx,Root[0][i-k-1],Root[0][i-1],1,n);if(pos!=-1)ans=min(ans,Minx+Maxx-pos*2+abs(sy-ty));
				pos=t1[0].Ask2(Maxx,n,Root[0][i-k-1],Root[0][i-1],1,n);if(pos!=-1)ans=min(ans,pos*2-Minx-Maxx+abs(sy-ty));
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}