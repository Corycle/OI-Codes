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
struct st{
	int a,b;
}num[100005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
int n,p[100005],tp;
bool cmp(st x,st y){
	return x.a<y.a;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(scanf("%d",&n)!=EOF){
		memset(p,0,sizeof(p));
		memset(num,0,sizeof(num));
		tp=0;
		for(i=1;i<=n;i++){j=read();num[j].a=i;}
		for(i=1;i<=n;i++){j=read();num[j].b=i;}
		sort(num+1,num+n+1,cmp);
		for(i=1;i<=n;i++){
			k=num[i].b;
			if(p[tp]<k)p[++tp]=k;
			else{
				int l=1,r=tp;
				while(l<=r){
					int mid=(l+r)/2;
					if(k>p[mid])l=mid+1;
					else r=mid-1;
				}
				p[l]=k;
			}
		}
		printf("%d\n",tp);
	}
	return 0;
}