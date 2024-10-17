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
//stack<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,k,a[100005];
queue<int>b;
queue<int>c;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%d",&n);
	int i,j,l,f=0,v;
	for(i=1;i<=n;i++){
		scanf("%d%d",&v,&k);
		for(j=1;j<=k;j++){
			scanf("%d",&l);
			b.push(v);
			c.push(l);
			a[l]++;
			if(a[l]==1)f++;
		}
		while(v-b.front()>=86400&&b.size()!=0){
			if(a[c.front()]==1)f--;
			a[c.front()]--;
			b.pop();
			c.pop();
		}
		printf("%d\n",f);
	}
	return 0;
}