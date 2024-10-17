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
int a[10];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k=0;
	for(i=8;i>=0;i--){
		scanf("%d",&a[i]);
		if(a[i]==0)continue;
		if(k==0){
			k=1;
			if(abs(a[i])!=1)printf("%d",a[i]);
			else if(a[i]==-1)printf("-");
		}
		else{
			if(a[i]<0)printf(" - ");
			else printf(" + ");
			if(abs(a[i])!=1)printf("%d",abs(a[i]));
		}
		if(i>1)printf("x^%d",i);
		if(i==1)printf("x");
		if(i==0&&abs(a[i])==1)printf("1");
	}
	if(k==0)printf("0");
	return 0;
}