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
int ans,a[20005],m,n;
int main(){
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++)a[i]=read();
	for(i=1;i<n;i++){
		if(a[i]+a[i+1]>ans)ans=a[i]+a[i+1];
	}
	for(i=1;i<=n;i++)m+=a[i];
	double mm=m,nn=n,tem;
	tem=ceil(mm/((int)(nn/2)));
	if((int)tem>ans)ans=(int)tem;
	printf("%d",ans);
	return 0;
}