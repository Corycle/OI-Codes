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
int n,m,a[505][505],ans;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			a[i][j]=a[j][i]=read();
		}
	}
	int maxx=-0x3f3f3f3f;
	for(i=1;i<=n;i++){
		maxx=m=0;
		for(j=1;j<=n;j++){
			if(a[i][j]>maxx){
				m=maxx;
				maxx=a[i][j];
			}
			else if(a[i][j]>m)m=a[i][j];
		}
		ans=max(ans,m);
	}
	printf("1\n%d",ans);
	return 0;
}