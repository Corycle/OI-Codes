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
long long n,m,p,a[10005],f[10005][105];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();p=read();
	for(i=1;i<=n;i++)a[i]=read();
	memset(f,-0x3f,sizeof(f));
	for(i=1;i<=n;i++)f[i][1]=max(f[i-1][1],a[i]);
	for(i=p;i<=n;i++){
		for(j=2;j<=m;j++){
			f[i][j]=max(f[i][j],f[i-1][j]);
			f[i][j]=max(f[i][j],f[i-p][j-1]+a[i]);
		}
	}
	printf("%lld",f[n][m]);
	return 0;
}