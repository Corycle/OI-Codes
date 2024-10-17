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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,ans1,ans2;
int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	ans1=ans2=read();
	for(i=2;i<=n;i++){
		int x=read();
		j=gcd(x,ans1);
		k=gcd(x,ans2);
		ans1=j;
		ans2=ans2/k*x;
	}
	printf("%d\n%d",ans1,ans2);
	return 0;
}