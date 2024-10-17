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
int n,k,f[100005],a[505],v[505],maxx;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&k,&n);
	for(i=1;i<=n;i++){
		scanf("%d%d",&a[i],&v[i]);
		maxx+=v[i];
	}
	for(i=1;i<=n;i++){
		for(j=k;j>=0;j--){
			if(j>=a[i])f[j]=max(f[j],f[j-a[i]]+v[i]);
		}
	}
	printf("%d",maxx-f[k]);
	return 0;
}
