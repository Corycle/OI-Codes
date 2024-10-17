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
long long n,m,a[150][150],g[150][150],d,ans,num;
int main(){
//	freopen("address.in","r",stdin);
//	freopen("address.out","w",stdout);
	long long i,j,k;
	d=read();n=read();
	for(i=1;i<=n;i++){
		j=read()+1;k=read()+1;
		a[j][k]=read();
	}
	for(i=1;i<=129;i++){
		for(j=1;j<=129;j++){
			g[i][j]=g[i-1][j]+g[i][j-1]-g[i-1][j-1]+a[i][j];
		}
	}
	for(i=1;i<=129;i++){
		for(j=1;j<=129;j++){
			long long x,y,p,q;
			x=min(129,int(i+d));
			y=min(129,int(j+d));
			p=max(1,int(i-d));
			q=max(1,int(j-d));
			k=g[x][y]+g[p-1][q-1]-g[x][q-1]-g[p-1][y];
			if(ans<k){
				ans=k;
				num=1;
			}
			else if(ans==k)num++;
		}
	}
	printf("%lld %lld",num,ans);
	return 0;
}