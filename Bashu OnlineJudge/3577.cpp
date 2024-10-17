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
int n,m,a[200005],f[200005];
struct _{
	int num,x;
};
deque<_>q;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		a[i]=read();
		while(q.size()&&q.front().x<=i-m)q.pop_front();
		while(q.size()&&(q.back().x<=i-m||a[i]<q.back().num))q.pop_back();
		_ now={a[i],i};
		q.push_back(now);
		f[i]=f[max(i-m,0)]+a[i];
		for(j=max(i-m,0);j<i;j++){
			f[i]=min(f[i],f[j]+a[i]);
		}
	}
	int ans=0x7fffffff/2;
//	for(i=1;i<=n;i++)cout<<f[i]<<endl;
	for(i=max(n-m+1,1);i<=n;i++){
		ans=min(ans,f[i]);
	}
	printf("%d",ans);
	return 0;
}