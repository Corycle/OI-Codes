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
int n,a[2005][2005],g[2005][2005],ans;
int sum(int i,int j,int k,int l){
	return g[k][l]-g[k][j-1]-g[i-1][l]+g[i-1][j-1];
}
int pd(int x,int y){
	int i,j,k;
	k=min(min(sum(x,1,x,y-1),sum(x,y+1,x,n)),min(sum(1,y,x-1,y),sum(x+1,y,n,y)));
	k++;
	while(1){
//		cout<<k<<endl;
		k--;
		if(k==0)return 1;
		if(sum(x-k,y-k,x-1,y-1))continue;
		if(sum(x+1,y+1,x+k,y+k))continue;
		if(sum(x-k,y+1,x-1,y+k))continue;
		if(sum(x+1,y-k,x+k,y-1))continue;
		return 2*k+1;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		char c[2005];
		scanf("%s",&c);
		for(j=1;j<=n;j++){
			a[i][j]=c[j-1]-'0';
			if(a[i][j])ans=1;
			g[i][j]=g[i-1][j]+g[i][j-1]-g[i-1][j-1]+a[i][j];
		}
	}
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(a[i][j])ans=max(ans,pd(i,j));
		}
	}
	printf("%d",ans);
	return 0;
}