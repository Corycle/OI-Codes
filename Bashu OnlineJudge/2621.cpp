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
int n,m,a[2505],b[2505],s,t;
bool p[2505];
int f[2505][2505],c[2505],minn;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n>>m>>s>>t;
	int i,j,k,l;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			f[i][j]=0xffffff;
		}
	}
	for(i=1;i<=m;i++){
		cin>>j>>k>>l;
		f[j][k]=f[k][j]=l;
	}
	
	for(i=1;i<=n;i++){
		c[i]=f[s][i];
	}
	memset(p,false,sizeof(p));
	c[s]=0;
	p[s]=true;
	for(i=1;i<=n-1;i++){
		minn=0xffffff;
		k=0;
		for(j=1;j<=n;j++){
			if((!p[j])&&c[j]<minn){
				minn=c[j];
				k=j;
			}
		}
		if(k==0)break;
		p[k]=true;
		for(j=1;j<=n;j++){
			if(c[k]+f[j][k]<c[j])c[j]=c[k]+f[k][j];
		}
	}
	cout<<c[t];
	return 0;
}