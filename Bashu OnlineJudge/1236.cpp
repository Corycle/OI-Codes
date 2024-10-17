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
//priority_queue<int,vector<int>,greater<int> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long n,m,c[1000005];
long long lowbit(long long x){
	return x&(-x);
}
void Add(long long x,long long y){
	while(x<=n){
		c[x]+=y;
		x+=lowbit(x);
	}
}
long long sum(long long x){
	long long ans=0;
	while(x){
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		long long x=read();
		Add(i,x);
		Add(i+1,-x);
	}
	while(m--){
		long long p=read();
		if(p==1){
			long long x=read(),y=read(),z=read();
			Add(x,z);
			Add(y+1,-z);
		}
		if(p==2){
			long long x=read();
			printf("%lld\n",sum(x));
		}
	}
	return 0;
}