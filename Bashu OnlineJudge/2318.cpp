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
#include<vector>
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
int n,m,a[105],b[105],f[105][55];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read()+3;
	if(2*m>n){
		printf("-1");
		return 0;
	}
	for(i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+n+1);
	for(i=2;i<=n;i++){
		b[i]=(a[i]-a[i-1])*(a[i]-a[i-1]);
	}
	memset(f,0x3f,sizeof(f));
	for(i=0;i<=n;i++)f[i][0]=0;
	for(i=2;i<=n;i++){
		for(j=1;j<=m;j++){
			f[i][j]=min(f[i-1][j],f[i-2][j-1]+b[i]);
		}
	}
	printf("%d",f[n][m]);
	return 0;
}