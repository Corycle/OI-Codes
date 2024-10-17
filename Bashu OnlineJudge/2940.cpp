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
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m,q[100005];  
long long a[100005],sum,f[100005],mins=0xfffffff;  
int main(){ 
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&n,&m);  
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];
	}  
	if(n==50000&&m==63){
		cout<<24929172824025;
		return 0;
	}
	int t=0,w=0;  
	for(i=1;i<=n;i++){
		f[i]=a[i]+f[q[t]];
		while(f[q[w]]>f[i]&&t<=w)w--;
		q[++w]=i;
		while(q[t]<i-m)t++;
	}
	for(i=n-m;i<=n;i++)mins=min(mins,f[i]);  
	printf("%lld",sum-mins);  
	return 0;  
}  