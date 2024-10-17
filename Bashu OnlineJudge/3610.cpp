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
int n,x2,x5,num=1;
int cal(int x){
	if(x<5)return 0;
	else{
		x/=5;
		return x+cal(x);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(scanf("%d",&n)!=EOF){
		printf("%d\n",cal(n));
	}
	return 0;
}