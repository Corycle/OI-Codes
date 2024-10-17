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
	int to,next;
}a[10000005];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,cnt,h[3005],p[3005],ans=0xfffff,f1[3005];
void yyx(int x,int y){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=h[x];
	h[x]=cnt;
}
bool cmp(int a1,int a2){
	return a1>a2;
}
int DP(int root){
	p[root]=1;
	int i,j=0,k=0,f[3505];
	/*
	f[root]=max{f[si]+i}
	*/
	for(i=h[root];i;i=a[i].next){
		if(p[a[i].to]==0){
			j++;
			f[j]=DP(a[i].to);
		}
	}
	sort(f+1,f+j+1,cmp);
	for(i=1;i<=j;i++){
		k=max(f[i]+i,k);
	}
	return k;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=2;i<=n;i++){
		cin>>j;
		yyx(j,i);
		yyx(i,j);
	}
	for(i=1;i<=n;i++){
		memset(p,0,sizeof(p));
		f1[i]=DP(i)+1;
		ans=min(ans,f1[i]);
	}
	cout<<ans<<endl;
	for(i=1;i<=n;i++){
		if(f1[i]==ans)cout<<i<<" ";
	}
	return 0;
}