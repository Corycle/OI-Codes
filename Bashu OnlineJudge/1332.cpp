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
int sum[1000005];
int pd(int x){
	int i,j,k;
	for(i=2;i<=sqrt(x);i++){
		if(x%i==0)return 0;
	}
	return 1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=2;i<=1000000;i++){
		sum[i]=sum[i-1]+pd(i);
	}
	while(scanf("%d%d",&j,&k)!=EOF){
		printf("%d\n",sum[k]-sum[j-1]);
	}
	return 0;
}