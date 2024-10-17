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
struct edge{
	int s,t,v;
}a[1000005];
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,f[1005],ans;
bool cmp(edge x,edge y){
	return x.v<y.v;
}
int g(int rt){
	int fa=f[rt];
	if(f[rt]!=rt)fa=g(f[rt]);
	f[rt]=fa;
	return fa;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		f[i]=i;
		for(j=1;j<=n;j++){
			scanf("%d",&k);
			if(j<=i)continue;
			m++;
			a[m].s=i;a[m].t=j;a[m].v=k;
		}
	}
	sort(a+1,a+m+1,cmp);
	for(i=1;i<=m;i++){
		j=g(a[i].s);
		k=g(a[i].t);
		if(j!=k){
			f[j]=k;
			ans+=a[i].v;
		}
	}
	printf("%d",ans);
	return 0;
}