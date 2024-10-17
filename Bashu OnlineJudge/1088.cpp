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
long long n,maxx,ans,num[12]={0,2,3,5,7,11,13,17,19,23};
void dfs(long long now,long long tot,long long u,long long v){
	if(maxx<tot||(tot==maxx&&ans>now)){
		maxx=tot;
		ans=now;
	}
	if(v>=10)return;
	for(long long i=1;i<=u;i++){
		now*=num[v];
		if(now>n)return;
		dfs(now,tot*(i+1),i,v+1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	dfs(1,1,500,1);
	printf("%lld",ans);
	return 0;
}