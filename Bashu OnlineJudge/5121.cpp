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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans;
int a[N],Cnt[N];
int *cnt=Cnt+50000;
int lmax[N],lmin[N],rmin[N],rmax[N];
void Calc(int l,int r,int mid){
	lmin[mid+1]=inf;rmax[mid]=-inf;
	lmax[mid+1]=-inf;rmin[mid]=inf;
	for(int i=mid;i>=l;i--){
		lmax[i]=max(lmax[i+1],a[i]);
		lmin[i]=min(lmin[i+1],a[i]);
	}
	for(int i=mid+1;i<=r;i++){
		rmax[i]=max(rmax[i-1],a[i]);
		rmin[i]=min(rmin[i-1],a[i]);
	}
	for(int i=l;i<=mid;i++){
		int j=i+lmax[i]-lmin[i];
		if(j>mid&&rmax[j]<lmax[i]&&rmin[j]>lmin[i])Ans++;
	}
	int p1=mid,p2=mid;
	for(int i=l;i<=mid;i++)cnt[i-lmin[i]]=0;
	for(int i=mid+1;i<=r;i++)cnt[i-rmax[i]]=0;
	while(p1<r&&rmax[p1+1]<lmax[l]){p1++;cnt[p1-rmax[p1]]--;}
	while(p2<r&&rmin[p2+1]>lmin[l]){p2++;cnt[p2-rmax[p2]]++;}
	for(int i=l;i<=mid;i++){
		while(p1>mid&&rmax[p1]>lmax[i]){cnt[p1-rmax[p1]]++;p1--;}
		while(p2>mid&&rmin[p2]<lmin[i]){cnt[p2-rmax[p2]]--;p2--;}
		Ans+=max(cnt[i-lmin[i]],0);
	}
	for(int i=l;i<=mid;i++)cnt[i-lmin[i]]=0;
	for(int i=mid+1;i<=r;i++)cnt[i-rmax[i]]=0;
}
void Divide(int l,int r){
	int mid=(l+r)>>1;
	if(l==r){Ans++;return;}
	Divide(l,mid);Divide(mid+1,r);
	Calc(l,r,mid);reverse(a+l,a+r+1);
	if((r-l+1)&1)mid--;
	Calc(l,r,mid);reverse(a+l,a+r+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[read()]=read();
	}
	Divide(1,n);
	printf("%d",Ans);
	return 0;
}