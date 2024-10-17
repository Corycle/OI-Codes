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
const int N=500005;
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
ll Ans;
int n,m,top1,top2;
int a[N],g1[N],g2[N],st1[N],st2[N];
int main(){
//	freopen("mem.in","r",stdin);
//	freopen("mem.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		st1[++top1]=i;g1[top1]=a[i];
		st2[++top2]=i;g2[top2]=a[i];
		for(int j=top1-1;j>=1;j--)g1[j]=__gcd(g1[j],g1[j+1]);
		for(int j=top2-1;j>=1;j--)g2[j]=g2[j]|g2[j+1];
		int t1=top1,t2=top2;top1=0;top2=0;
		for(int j=1;j<=t1;j++){
			st1[++top1]=st1[j];g1[top1]=g1[j];
			while(j<t1&&g1[j]==g1[j+1])j++;
		}
		for(int j=1;j<=t2;j++){
			st2[++top2]=st2[j];g2[top2]=g2[j];
			while(j<t2&&g2[j]==g2[j+1])j++;
		}
		int j=1,k=1;
		st1[top1+1]=i+1;
		st2[top2+1]=i+1;
		while(j<=top1&&k<=top2){
			if((g1[j]^g2[k])==m){
				int l=max(st1[j],st2[k]);
				int r=min(st1[j+1],st2[k+1])-1;
				if(l<=r)Ans+=(r-l+1);
			}
			if(st1[j+1]<=st2[k+1])j++;
			else if(st1[j+1]>st2[k+1])k++;
		}
	}
	printf("%lld",Ans);
	return 0;
}