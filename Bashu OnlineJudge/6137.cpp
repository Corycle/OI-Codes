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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];
double Ans[N];
double Calc(int x,int y){
	return sqrt(x-y)+a[y]-a[x];
}
void Divide(int l,int r,int ql,int qr){
	int mid=(l+r)>>1,pos=ql;
	for(int i=ql;i<=qr&&i<=mid;i++){
		if(Calc(mid,pos)<Calc(mid,i))pos=i;
	}
	Ans[mid]=max(Ans[mid],Calc(mid,pos));
	if(l<mid)Divide(l,mid-1,ql,pos);
	if(r>mid)Divide(mid+1,r,pos,qr);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Divide(1,n,1,n);reverse(a+1,a+n+1);reverse(Ans+1,Ans+n+1);
	Divide(1,n,1,n);reverse(a+1,a+n+1);reverse(Ans+1,Ans+n+1);
	for(int i=1;i<=n;i++)printf("%.0lf\n",ceil(Ans[i]));
	return 0;
}