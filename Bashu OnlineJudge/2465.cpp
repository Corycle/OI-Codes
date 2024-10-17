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
int m,n,a[505][505],p[505][505],num;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	m=read();n=read();
	memset(a,0x3f,sizeof(a));
	for(i=1;i<=m;i++){
		num=0;
		char c=' ';
		while(c!=10&&c!=13){
			num++;
			scanf("%d",&p[i][num]);
			c=getchar();
			for(j=1;j<num;j++){
				a[p[i][j]][p[i][num]]=1;
			}
		}
	}
	for(i=1;i<=n;i++)a[i][i]=0;
	for(k=1;k<=n;k++){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	if(a[1][n]==0x3f3f3f3f)printf("NO");
	else printf("%d",a[1][n]-1);
	return 0;
}