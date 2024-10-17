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
#define y1 y_1
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],b[N];
int Check(int x1,int y1,int x2,int y2){
	double k1=-(double)y1/x1;
	double k2=(double)y2/x2;
	double x=y1/(k2-k1);
	return x<=x2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1);sort(b+1,b+n+1);
	m=read();
	while(m--){
		int x=read(),y=read();
		int l=1,r=n,Ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(a[mid],b[mid],x,y)){
				Ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		printf("%d\n",Ans);
	}
	return 0;
}