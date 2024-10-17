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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	p[i]>=a[j]-a[i]+sqrt(abs(i-j));
	p[i]=max{a[j]+sqrt(abs(i-j))}-a[i];
*/
int n,m;
int a[N];
double ans[N];
struct node{
	int l,r,p;
}q[N];
double Val(int j,int i){
	return a[j]+sqrt(i-j);
}
int Find(int p1,int p2,int l,int r){
	while(l<r){
		int mid=(l+r)>>1;
		if(Val(p1,mid)>=Val(p2,mid))l=mid+1;
		else r=mid;
	}
	return l;
}
void DP(){
	int l=1,r=1;
	q[1]=(node){2,n,1};
	for(int i=2;i<=n;i++){
		while(l<=r&&q[l].r<i)l++;
		ans[i]=max(ans[i],Val(q[l].p,i));
		q[l].l=i+1;
		while(l<=r&&Val(q[r].p,q[r].l)<Val(i,q[r].l))r--;
		if(l>r)q[++r]=(node){i+1,n,i};
		else{
			if(Val(q[r].p,q[r].r)<Val(i,q[r].r)){
				int x=Find(q[r].p,i,q[r].l,q[r].r);
				q[r].r=x-1;
				q[++r]=(node){x,n,i};
			}
			else if(q[r].r!=n){
				int R=q[r].r;
				q[++r]=(node){r+1,n,i};
			}
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	DP();
	for(int i=1;i<=n/2;i++){
		swap(a[i],a[n-i+1]);
		swap(ans[i],ans[n-i+1]);
	}
	DP();
	for(int i=n;i>=1;i--){
		printf("%d\n",max((int)ceil(ans[i]-a[i]),0));
	}
	return 0;
}