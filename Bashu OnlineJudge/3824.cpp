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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<long long,vector<long long>,greater<long long> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long n,m,p,t=1;
long long spow(long long x,long long y){
	long long tot=x,ans=1;
	while(y){
		if(y&1)ans=ans*tot%n;
		tot=tot*tot%n;
		y/=2;
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	long long i,j,k;
	n=read();m=read();p=read();
	t=spow(10,p);
	t=t*m%n;
	long long x=read();
	x=(x+t)%n;
	printf("%lld",x);
	return 0;
}