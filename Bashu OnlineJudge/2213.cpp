#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int n,m,a[3005][3005],l[3005][3005],r[3005][3005],h[3005][3005],p,lcx[3005][3005];
int ans;
int main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	int i,j,k;
	n=read();m=read();p=read();
	for(i=1;i<=p;i++){
		int x=read(),y=read();
		lcx[x][y]=1;
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++)a[i][j]=1-lcx[i][j];
		for(j=1;j<=m;j++)if(a[i][j])l[i][j]=l[i][j-1]+1;
		for(j=m;j>=1;j--)if(a[i][j])r[i][j]=r[i][j+1]+1;
		for(j=1;j<=m;j++){
			if(!a[i][j])continue;
			if(a[i-1][j]){
				l[i][j]=min(l[i][j],l[i-1][j]);
				r[i][j]=min(r[i][j],r[i-1][j]);
			}
			h[i][j]=h[i-1][j]+1;
			ans=max(ans,(l[i][j]+r[i][j]-1)*h[i][j]);
		}
	}
	printf("%d",ans);
	return 0;
}