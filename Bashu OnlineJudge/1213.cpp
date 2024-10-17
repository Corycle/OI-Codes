#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long x,y,m,n,l,d;
void gcd(long long a,long long b,long long &x,long long &y){
	if(!b){
		x=1;y=0;
		d=a;
	}
	else{
		gcd(b,a%b,x,y);
		int t=x;
		x=y;
		y=t-a/b*y;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	x=read();y=read();m=read();n=read();l=read();
	long long a,b;
	gcd(n-m,l,a,b);
	if((x-y)%d!=0||m==n)printf("Impossible");
	else printf("%lld",(a*(x-y)/d%(l/d)+(l/d))%(l/d));
	return 0;
}