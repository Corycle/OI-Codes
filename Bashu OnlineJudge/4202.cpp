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
const int N=40005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],f[N];
struct Node{int x,y,z,id;}P[N];
bool cmp1(Node A,Node B){return A.x<B.x;}
bool cmp2(Node A,Node B){return A.y<B.y;}
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]=max(c[x],y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=max(ans,c[x]);return ans;}
	void Clear(int x){for(;x<=n;x+=lowbit(x))c[x]=0;}
}tree;
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	sort(P+l,P+r+1,cmp1);
	CDQ(l,mid);
	sort(P+l,P+mid+1,cmp2);
	sort(P+mid+1,P+r+1,cmp2);
	int p1=l,p2=mid+1;
	while(p2<=r){
		while(p1<=mid&&P[p1].y<P[p2].y){
			tree.Add(P[p1].z,f[P[p1].id]+1);p1++;
		}
		f[P[p2].id]=max(f[P[p2].id],tree.Ask(P[p2].z));p2++;
	}
	for(int i=l;i<=p1;i++)tree.Clear(P[i].z);
	CDQ(mid+1,r);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].y=read();
		P[i].z=read();
		a[i]=P[i].z;
		P[i].id=i;
		f[i]=1;
	}
	sort(a+1,a+n+1);a[0]=unique(a+1,a+n+1)-a-1;
	for(int i=1;i<=n;i++)P[i].z=lower_bound(a+1,a+a[0]+1,P[i].z)-a;
	CDQ(1,n);
	for(int i=1;i<=n;i++)Ans=max(Ans,f[i]);
	printf("%d",Ans);
	return 0;
}