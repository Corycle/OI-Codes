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
const int N=6e5+5;
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
int n,m,Ans;
int a[N],cnt[N],num[N],Min[N],Max[N],Pos[N],lst[N];
void Calc(int l,int r,int mid){
	Min[mid]=inf;Max[mid]=-inf;
	for(int i=mid+1;i<=r;i++)Min[i]=min(Min[i-1],a[i]);
	for(int i=mid+1;i<=r;i++)Max[i]=max(Max[i-1],a[i]);
	for(int i=l;i<=r;i++){num[a[i]]=0;Pos[i]=lst[a[i]]=r+1;}Pos[r+1]=r+1;
	for(int i=r;i>=l;i--){Pos[i]=min(Pos[i+1],lst[a[i]]);lst[a[i]]=i;}
	for(int i=mid,MAX=-inf,MIN=inf;i>=l;i--){
		MAX=max(MAX,a[i]);MIN=min(MIN,a[i]);int j=i+MAX-MIN;
		if(j>mid&&j<Pos[i]&&Max[j]<MAX&&Min[j]>MIN&&MIN==1)Ans++;
	}
	for(int i=mid,p1=mid,p2=mid+1,MAX=-inf,MIN=inf;i>=l;i--){
		if((++num[a[i]])==2)break;
		MAX=max(MAX,a[i]);MIN=min(MIN,a[i]);
		while(p1<r&&p1<Pos[i]&&Max[p1+1]<MAX){p1++;cnt[p1+Min[p1]]++;}
		while(p1>=Pos[i]&&p1>mid){cnt[p1+Min[p1]]--;p1--;}
		while(p2<=r&&Min[p2]>1){cnt[p2+Min[p2]]--;p2++;}
		if(Min[p2]==1)Ans+=max(cnt[i+MAX],0);
	}
	for(int i=mid+1;i<=r;i++)cnt[i+Min[i]]=0;
}
void Solve(int l,int r){
	if(l==r){Ans+=(a[l]==1);return;}
	int mid=(l+r)>>1;
	Solve(l,mid);Solve(mid+1,r);
	Calc(l,r,mid);reverse(a+l,a+r+1);
	if((r-l+1)&1)mid--;
	Calc(l,r,mid);reverse(a+l,a+r+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Solve(1,n);
	printf("%d\n",Ans);
	return 0;
}
