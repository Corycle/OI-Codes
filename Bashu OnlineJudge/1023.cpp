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
int n,a[5005],p[1000005],maxx;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		a[i]=read();
		maxx=max(maxx,a[i]);
		for(j=1;j<i;j++){
			p[abs(a[i]-a[j])]=1;
		}
	}
	for(i=n;i<=maxx;i++){
		int t=i,flag=1;
		while(t<=maxx){
			if(p[t]){
				flag=0;
				break;
			}
			t+=i;
		}
		if(flag){
			printf("%d",i);
			return 0;
		}
	}
	return 0;
}