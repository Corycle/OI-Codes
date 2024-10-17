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
const int N=50005;
const int M=32;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N];
struct Line_Basis{
	int num,a[M];
	void Clear(){num=0;memset(a,0,sizeof(a));}
	void Insert(int x){
		for(int i=30;i>=0;i--){
			if((x>>i)&1){
				if(!a[i]){a[i]=x;num++;break;}
				x^=a[i];
			}
		}
	}
	void Build(){
		for(int i=30;i>=0;i--){
			for(int j=i-1;j>=0;j--){
				if((a[i]>>j)&1)a[i]^=a[j];
			}
		}
	}
	friend Line_Basis operator+(Line_Basis A,Line_Basis B){
		if(A.num<B.num)swap(A,B);
		for(int i=30;i>=0;i--)if(B.a[i])A.Insert(B.a[i]);
		return A;
	}
}Ans;
struct Segment_Tree{
	Line_Basis t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Insert(a[l]);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Update(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Clear();t[p].Insert(a[l]);return;}
		int mid=(l+r)>>1;
		Update(x,lson);Update(x,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){Ans=Ans+t[p];return;}
		int mid=(l+r)>>1;
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
int t[M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	while(m--){
		int op=read(),x=read(),y=read();
		if(op==1){a[x]=y;tree.Update(x,1,1,n);}
		if(op==2){
			Ans.Clear();
			tree.Query(x,y,1,1,n);
			Ans.Build();
			int sum=0;t[0]=0;
			for(int j=0;j<=30;j++)if(Ans.a[j])t[++t[0]]=Ans.a[j];
			for(int j=30;j>=0;j--)sum=max(sum,sum^Ans.a[j]);
			ll ans=1ll*sum*((y-x+1)-Ans.num+1);
			for(int j=1;j<t[0];j++)ans+=max(t[j],sum^t[j]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}