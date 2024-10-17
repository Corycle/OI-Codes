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
int n,m,f[305][305],p[305],s;
void dzh(int root,int fp){
	p[root]=1;
	if(fp==n)return;
	int i,j,k=100000000,x,y;
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			if(f[i][j]!=0){
				if(p[i]==1&&p[j]==0&&k>f[i][j]){
					k=f[i][j];
					x=i;y=j;
				}
				else if(p[i]==0&&p[j]==1&&k>f[i][j]){
					k=f[i][j];
					y=i;x=j;
				}
			}
		}
	}
	s+=k;
	dzh(y,fp+1);
}
int main(){
	cin>>n>>m;
	int i,j,k,l;
	for(i=1;i<=m;i++){
		cin>>j>>k>>l;
		f[j][k]=f[k][j]=l;
	}
	dzh(1,1);
	cout<<s;
	return 0;
}