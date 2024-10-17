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
int n,m,g[100005],maxx=1,sum[100005];
int Find(int x){
	return x==g[x]?x:g[x]=Find(g[x]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		g[i]=i;
		sum[i]=1;
	}
	while(m--){
		int p=read();
		if(p==2)printf("%d\n",maxx);
		else{
			int x=Find(read()),y=Find(read());
			if(x!=y){
				g[x]=y;
				sum[y]+=sum[x];
				maxx=max(maxx,sum[y]);
			}
		}
	}
	return 0;
}