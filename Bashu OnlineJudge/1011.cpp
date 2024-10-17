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
int a[10][10]={
	{0,0,0,0,0,0},
	{0,5,-1,-2,-1,-3},
	{0,-1,5,-3,-2,-4},
	{0,-2,-3,5,-2,-2},
	{0,-1,-2,-2,5,-1},
	{0,-3,-4,-2,-1,0},
};
int f[105][105],s1[105],s2[105],l1,l2;
int main(){
	int i,j,k;
	char l;
	cin>>l1;
	for(i=1;i<=l1;i++){
		cin>>l;
		if(l=='A')s1[i]=1;
		if(l=='C')s1[i]=2;
		if(l=='G')s1[i]=3;
		if(l=='T')s1[i]=4;
	}
	cin>>l2;
	for(i=1;i<=l2;i++){
		cin>>l;
		if(l=='A')s2[i]=1;
		if(l=='C')s2[i]=2;
		if(l=='G')s2[i]=3;
		if(l=='T')s2[i]=4;
	}
	for(i=1;i<=l1;i++){
		for(j=1;j<=l2;j++){
			f[i][j]=-0xfffff;
		}
	}
	for(i=1;i<=l1;i++)f[i][0]=f[i-1][0]+a[s1[i]][5];
	for(i=1;i<=l2;i++)f[0][i]=f[0][i-1]+a[s2[i]][5];
	for(i=1;i<=l1;i++){
		for(j=1;j<=l2;j++){
			f[i][j]=max(f[i][j],f[i][j-1]+a[s2[j]][5]);
			f[i][j]=max(f[i][j],f[i-1][j]+a[s1[i]][5]);
			f[i][j]=max(f[i][j],f[i-1][j-1]+a[s1[i]][s2[j]]);
		}
	}
	cout<<f[l1][l2];
	return 0;
}