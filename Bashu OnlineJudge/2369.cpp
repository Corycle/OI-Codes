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
int n,m,a[1005][1005],l[1005][1005],r[1005][1005],h[1005][1005];
int ans;
int main(){
//	freopen("easy.in","r",stdin);
//	freopen("easy.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			char c;
			cin>>c;
			if(c=='F')a[i][j]=1;
		}
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
	printf("%d",3*ans);
	return 0;
}