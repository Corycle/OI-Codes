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
const int N=2e5+5;
const int M=400;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum,Ans[N];
int n,m,num,a[N],L[N],R[N],st[N],ed[N],pos[N];
struct Point{
	int x,y;
	double Alpha(){return atan2(y,x);}
	friend ll operator^(Point A,Point B){return 1ll*A.x*B.y-1ll*A.y*B.x;}
}P[N];
struct Ques{int l,r,id;}Q[N];
bool cmp1(int x,int y){return P[x].Alpha()<P[y].Alpha();}
bool cmp2(Ques A,Ques B){return pos[A.l]!=pos[B.l]?pos[A.l]<pos[B.l]:A.r>B.r;}
void Prepare(){
	while(ed[num]!=n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
}
void Update(int x,int addv){
	if(addv==-1){
		int l=L[x],r=R[x];
		Sum=Sum-(P[l]^P[x])-(P[x]^P[r])+(P[l]^P[r]);
		L[r]=l;R[l]=r;
	}
	else{
		int l=L[x],r=R[x];
		Sum=Sum-(P[l]^P[r])+(P[l]^P[x])+(P[x]^P[r]);
		L[r]=x;R[l]=x;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Prepare();
	for(int i=1;i<=n;i++){P[i].x=read();P[i].y=read();a[i]=i;}
	sort(a+1,a+n+1,cmp1);a[0]=a[n];a[n+1]=a[1];
	for(int i=1;i<=n;i++){L[a[i]]=a[i-1];R[a[i]]=a[i+1];Sum+=(P[a[i]]^P[a[i+1]]);}
	for(int i=1;i<=m;i++){Q[i].l=read();Q[i].r=read();Q[i].id=i;}
	sort(Q+1,Q+m+1,cmp2);
	int p=1,l=1,r=n;
	for(int i=1;i<=num;i++){
		while(p<=m&&pos[Q[p].l]==i){
			while(r>Q[p].r)Update(r--,-1);
			while(l<Q[p].l)Update(l++,-1);
			Ans[Q[p].id]=Sum;
			while(l>st[i])Update(--l,1);
			p++;
		}
		while(r<n)Update(++r,1);
		while(l<=ed[i])Update(l++,-1);
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Ans[i]);
	return 0;
}