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
long long n,m,a[2000005],s=1,t=0,sum=0,ans=0x3f3f3f3f;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
//	for(i=1;i<=n;i++)a[i]=read();
	while(1){
		while(sum<m&&t<n){
			a[++t]=read();
			sum+=a[t];
		}
		if(sum>=m)ans=min(ans,t-s+1);
		while(sum>=m&&s<=t){
			sum-=a[s++];
			if(sum>=m)ans=min(ans,t-s+1);
		}
		if(t==n)break;
	}
	printf("%lld",ans);
	return 0;
}