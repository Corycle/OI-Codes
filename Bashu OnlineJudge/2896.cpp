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
int n,m,a[105][105],ans=0x3f3f3f3f;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	memset(a,0x3f,sizeof(a));
	for(i=1;i<=n;i++)a[i][i]=0;
	for(i=1;i<=m;i++){
		j=read();k=read();
		a[j][k]=a[k][j]=read();
	}
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	int x=0,y=0;
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			int sum=0;
			for(k=1;k<=n;k++){
				sum+=min(a[k][i],a[k][j]);
			}
			if(ans>sum){
				ans=sum;
				x=i;y=j;
			}
		}
	}
	printf("%d %d",x,y);
	return 0;
}