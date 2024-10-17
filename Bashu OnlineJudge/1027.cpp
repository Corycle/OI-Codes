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
struct tree{int x,y,p;}a[105];
int n,q,f[105][105],f1[105][105],f2[105],f3[105],ans;
void DFS(int root){
	f2[root]=1;
	int i,j,k;
	for(i=1;i<=n;i++){
		if(f2[i]==0&&f1[root][i]>=0){
			f3[i]=f1[root][i];
			if(a[root].x==0){
				a[root].x=i;
				DFS(i);
			}
			else if(a[root].y==0){
				a[root].y=i;
				DFS(i);
				break;
			}
		}
	}
}
int DP(int root,int t){
	int i,j,k;
	if(a[root].x==0&&a[root].y==0){
		if(t==0)return 0;
		if(t==1)return f3[root];
		return -0xfffff;
	}
	if(f[root][t]>0)return f[root][t];
	for(i=0;i<t;i++){
		f[root][t]=max(f[root][t],DP(a[root].x,i)+DP(a[root].y,t-i-1)+f3[root]);
	}
	return f[root][t];
}
int main(){
	int i,j,k,l;
	cin>>n>>q;q++;
	memset(f1,-1,sizeof(f1));
	for(i=1;i<n;i++){
		cin>>j>>k>>l;
		f1[j][k]=f1[k][j]=l;
	}
	DFS(1);
	cout<<DP(1,q);
	return 0;
}