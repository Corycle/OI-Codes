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
int t;
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int gcd(int x,int y){
	if(x<y)swap(x,y);
	return y==0?x:gcd(y,x%y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	t=read();
	while(t--){
		int a=read(),b=read(),c=read(),d=read();
		int x=a*d-b*c,y=b*d;
		int f=1;
		if(x<0)f*=-1;
		x=abs(x);y=abs(y);
		int mod=gcd(x,y);
		x/=mod;y/=mod;
		if(f<0)printf("-");
		if(x==0)printf("0\n");
		else if(x%y==0)printf("%d\n",x/y);
		else printf("%d/%d\n",x,y);
	}
	return 0;
}