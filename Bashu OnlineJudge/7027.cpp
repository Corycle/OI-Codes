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
const int N=1e6+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];ll K;
int l0=1,l1=1,r0,r1,r2,q[N],q0[N],q1[N],q2[N],R[N];
int main(){
//	freopen("mobiliarbus.in","r",stdin);
//	freopen("mobiliarbus.out","w",stdout);
	n=read(),K=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]==0)q0[++r0]=i;
		if(a[i]==1)q1[++r1]=i;
		if(a[i]==2)q2[++r2]=i;
	}
	q2[++r2]=n+1;
	int pos=0;
	for(int l2=1;l2<=r2;l2++){
		int x=q2[l2],top=0,num=0;
		while(l0<=r0||l1<=r1){
			if((l1>r1)||(l0<=r0&&q0[l0]<q1[l1])){
				if(q0[l0]<x)q[++top]=q0[l0++];
				else break;
			}
			else {
				if(q1[l1]<x)q[++top]=q1[l1++];
				else break;
			}
		}
		for(int i=1;i<=top;i++)
		if(a[q[i]]==0){
			int v=i-num-1;
			if(v<=K)num++,K-=v,swap(q[num],q[i]);
			else{
				int t=i-K-1;
				K=0,swap(q[t+1],q[i]);
			}
		}
		for(int i=1;i<=top;i++)R[++pos]=a[q[i]];
		while(l1<=r1){
			int v=q1[l1]-pos-1;
			if(v<=K)R[++pos]=1,K-=v,l1++;
			else break;
		}
		R[++pos]=2;
	}
	for(int i=1;i<=n;i++)cout<<R[i]<<" ";
	return 0;
}