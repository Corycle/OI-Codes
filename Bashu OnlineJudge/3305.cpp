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
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int n,h,d,f[2005][2005],num,ans,p[2005][2005],g[2005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();h=read();d=read();
	for(i=1;i<=n;i++){
		num=read();
		for(j=1;j<=num;j++){
			int hi=read();
			p[i][hi]++;
		}
	}
	for(i=1;i<=n;i++)f[i][0]=p[i][0];
	for(j=1;j<=h;j++){
		for(i=1;i<=n;i++)f[i][j]=f[i][j-1]+p[i][j];
		if(j>=d)for(i=1;i<=n;i++)f[i][j]=max(f[i][j],g[j-d]+p[i][j]);
		for(i=1;i<=n;i++)g[j]=max(f[i][j],g[j]);
	}
	printf("%d",g[h]);
	return 0;
}