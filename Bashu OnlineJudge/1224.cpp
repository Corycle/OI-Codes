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
int n,m,ans[100005],c[100005];
struct stars{
	int x,y;
}a[100005];
int lowbit(int x){
	return (x&(-x));
}
int sum(int x){
	int ans=0;
	while(x!=0){
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}
void update(int x,int y){
	while(x<=n){
		c[x]+=y;
		x+=lowbit(x);
	}
}
bool cmp(stars x,stars y){
	if(x.x==y.x)return x.y<y.y;
	return x.x<y.x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
    	a[i].x=read()+1;
		a[i].y=read()+1;
		m=max(m,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++){
		ans[sum(a[i].y)]++;
		update(a[i].y,1);
	}
	for(i=0;i<n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}