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
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int p,n,a[1005];
void poww(){
	int c[1005];
	memset(c,0,sizeof(c));
	for(int i=1;i<=500;i++){
		for(int j=1;j<=500;j++){
			c[i+j-1]+=a[i]*a[j];
		}
	}
    for(int i=1;i<=500;i++){
    	if(c[i]/10!=0){
			c[i+1]+=c[i]/10;
			c[i]%=10;
		}
	}
	for(int i=1;i<=500;i++)a[i]=c[i];
}
void cheng(){
	int i,j,k;
	for(i=1;i<=500;i++)a[i]*=2;
	for(i=1;i<=500;i++){
		if(a[i]/10!=0){
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
	}	
}
void f(int x){//快速幂 
    if(x/2!=1)f(x/2);
    poww();
    if(x%2==1)cheng();
}
main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&p);
    n=ceil(p*log10(2));
    printf("%d\n",n);
    a[1]=2;
    f(p);
    a[1]--;
    for(i=500;i>=1;i--){
		printf("%d",a[i]);
		if((i-1)%50==0)printf("\n");
    }
    return 0;
}