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
int n;
double x,y;
pair<double,double>a[20005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		double aa,bb;
		scanf("%lf%lf",&aa,&bb);
		x+=aa;y+=bb;
		a[i]=make_pair(aa,bb);
	}
	x/=n;y/=n;
	sort(a+1,a+n+1);
	for(i=1;i<=n/2;i++){
		if(x!=(a[i].first+a[n-i+1].first)/2||y!=(a[i].second+a[n-i+1].second)/2){
			printf("This is a dangerous situation.");
			return 0;
		}
	}
	printf("V.I.P. should stay at (%.1lf,%.1lf).",x,y);
	return 0;
}