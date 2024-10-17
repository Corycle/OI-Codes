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
const int Mod=1e6+777;
const int M=1000005;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt;
int p[M],c[M],lst[M],Root[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Divide(int x){
	cnt=0;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			p[++cnt]=i;c[cnt]=0;
			while(x%i==0){c[cnt]++;x/=i;}
		}
	}
	if(x!=1){p[++cnt]=x;c[cnt]=1;}
}
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*80];
	void Insert(int &x,int y,int pos,int val,int l,int r){
		x=++tot;t[x]=t[y];t[x].sum=1ll*val*t[y].sum%Mod;
		if(l==r)return;int mid=(l+r)>>1;
		if(pos<=mid)Insert(t[x].l,t[y].l,pos,val,l,mid);
		if(pos>mid)Insert(t[x].r,t[y].r,pos,val,mid+1,r);
	}
	int Query(int p,int x,int y,int l,int r){
		if(y<l||x>r||!p)return 1;
		if(x<=l&&r<=y)return t[p].sum;
		int mid=(l+r)>>1;
		return 1ll*Query(t[p].l,x,y,l,mid)*Query(t[p].r,x,y,mid+1,r)%Mod;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	tree.t[0].sum=1;
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read();Divide(x);
		int sum=1;Root[i]=Root[i-1];
		for(int j=1;j<=cnt;j++){
			if(lst[p[j]]){
				int val=1ll*p[j]*Pow(p[j]-1,Mod-2)%Mod;
				tree.Insert(Root[i],Root[i],lst[p[j]],val,1,n);
			}
			sum=1ll*sum*(p[j]-1)%Mod*Pow(p[j],c[j]-1)%Mod;
			lst[p[j]]=i;
		}
		tree.Insert(Root[i],Root[i],i,sum,1,n);
	}
	int Ans=0;
	while(m--){
		int l=read()^Ans,r=read()^Ans;
		printf("%d\n",Ans=tree.Query(Root[r],l,r,1,n));
	}
	return 0;
}