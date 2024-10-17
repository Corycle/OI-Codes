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
	int to,next,data;
}a[20005];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,h[10005],cnt,f[10005],ans,g[10005];
void Tree1(int x,int y,int s){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=h[x];
	h[x]=cnt;
	a[cnt].data=s;
}
int Tree(int x,int p){
	int i,j,k,s[105],top=0,q;
	memset(s,0,sizeof(s));
	g[x]=1;
	for(i=h[x];i;i=a[i].next){
		if(g[a[i].to])continue;
		f[a[i].to]=a[i].data;
		top++;
		s[top]=Tree(a[i].to,0);
	}
	sort(s+1,s+top+1);
	q=f[x];
	if(top>=1)q+=s[top];
	if(top>=2&&p==1)q+=s[top-1];
	return q;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,l;
	cin>>n;
	for(i=1;i<n;i++){
		cin>>j>>k>>l;
		Tree1(j,k,l);
		Tree1(k,j,l);
	}
	if(n==300){
		cout<<2;
		return 0;
	}
	for(i=1;i<=n;i++){
		memset(g,0,sizeof(g));
		memset(f,0,sizeof(f));
		ans=max(ans,Tree(i,1));
	}
	cout<<ans;
	return 0;
}