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
const int Mod=1e9+7;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int L[N],R[N],s[N],f[N],sum[N];
struct Node{int x,y;}a[N],P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
bool cmp1(Node A,Node B){return A.y!=B.y?A.y<B.y:A.x<B.x;}
bool cmp2(Node A,Node B){return A.x!=B.x?A.x<B.x:A.y<B.y;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i].x=read();a[i].y=read();}
	sort(a+1,a+n+1,cmp1);
	s[0]=0;
	for(int i=1;i<=n;i++){
		int l=1,r=i;s[i]=max(s[i-1],a[i].x);
		while(l<=r){int mid=(l+r)>>1;if(s[mid]>=a[i].x){P[i].x=mid;r=mid-1;}else l=mid+1;}
	}
	s[n+1]=inf;
	for(int i=n;i>=1;i--){
		int l=i,r=n;s[i]=min(s[i+1],a[i].x);
		while(l<=r){int mid=(l+r)>>1;if(s[mid]<=a[i].x){P[i].y=mid;l=mid+1;}else r=mid-1;}
	}
	sort(P+1,P+n+1,cmp2);
	int j=0;f[0]=sum[0]=1;
	for(int i=1;i<=n;i++){
		while(P[j].y<P[i].x-1)j++;
		f[i]=mod(sum[i-1]-sum[j-1]+Mod);
		sum[i]=mod(sum[i-1]+f[i]);
	}
	while(P[j].y<n)j++;
	printf("%d\n",mod(sum[n]-sum[j-1]+Mod));
	return 0;
}
