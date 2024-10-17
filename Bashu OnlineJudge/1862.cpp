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
struct _{
	int x,y;
}a[50005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n;
bool cmp(_ a1,_ a2){
	if(a1.x!=a2.x)return a1.x<a2.x;
	return a1.y<a2.y;
}
void init(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
	}
}
void solve(){
	int i,j,k,l=0,r=0;
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++){
		if(r<a[i].x){
			if(l!=0){
				printf("%d %d\n",l,r);
			}
			l=a[i].x;
			r=a[i].y;
		}
		else r=max(a[i].y,r);
	}
	printf("%d %d\n",l,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	init();
	solve();
	return 0;
}