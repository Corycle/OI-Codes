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
int n,m,f[1000001][23];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++)f[i][0]=read();
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
	while(m--){
		i=read();j=read();
		k=int(log(j-i+1)/log(2));
		printf("%lld\n",max(f[i][k],f[j+1-(1<<k)][k]));
	}
	return 0;
}