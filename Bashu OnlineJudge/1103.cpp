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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int maxx=200005;
struct Edge{
	int to,next;
}a[400010];
int h[200005],cnt,sum[200005],v[200005],n;
void haha(int x,int y){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=h[x];
	h[x]=cnt;
}
void gg(int x,int p){
	int i,y;
	sum[x]=v[x];
	for(i=h[x];i;i=a[i].next){
		y=a[i].to;
		if(y==p)continue;
		gg(y,x);
		sum[x]+=sum[y];
	}
}
int main(){
	int i,x,y,ans,k;
	cin>>n;
	for(i=1;i<=n;i++)cin>>v[i];
	for(i=1;i<n;i++){
		cin>>x>>y;
		haha(x,y);
		haha(y,x);
	}
	gg(1,0);
	ans=-0x7fffffff/2;
	for(i=1;i<=n;i++){
		if(sum[i]>ans){
			ans=sum[i];
			k=i;
		}
	}	
	cout<<k<<" "<<ans;
	return 0;
}