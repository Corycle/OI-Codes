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
int n,m,mod=32768,w[3][3],c[100],a[3][3],b[3][3];
void yyx(int a[][3],int b[][3]){
	int i,j,k;
	memset(w,0,sizeof(w));
	for(i=1;i<=2;i++){
		for(j=1;j<=2;j++){
			for(k=1;k<=2;k++){
				w[i][j]=(w[i][j]+a[i][k]*b[k][j])%mod;
			}
		}
	}
	memcpy(a,w,sizeof(w));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int ans;
	cin>>n;
	if(n<=2){
		cout<<1;
		return 0;
	}
	n-=2;
	while(n>0){
		c[++c[0]]=n%2;
		n/=2;
	}
	a[1][1]=0;
	a[1][2]=a[2][1]=a[2][2]=1;
	memcpy(b,a,sizeof(a));
	for(i=c[0]-1;i>=1;i--){
		yyx(a,a);
		if(c[i]==1)yyx(a,b);
	}
	ans=(a[1][2]+a[2][2])%mod;
	cout<<ans;
	return 0;
}