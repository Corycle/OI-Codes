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
int n,a[100005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n-2;i++)a[i]=read();
	sort(a+1,a+n-1);
	if(a[1]>1)printf("1 ");
	if(a[1]>2)printf("2 ");
	for(i=2;i<=n-2;i++){
		if(a[i]!=a[i-1]+1){
			printf("%d ",a[i-1]+1);
		}
	}
	if(a[n-2]<n-1)printf("%d ",n-1);
	if(a[n-2]<n)printf("%d ",n);
	return 0;
}