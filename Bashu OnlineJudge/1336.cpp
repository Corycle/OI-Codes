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
int f(int n){
   if(n<5)return 0;
   return n/5+f(n/5);
}
int main()
{
	int a;
	while(cin>>a){
		printf("%d\n", f(a));
	}
   
   return 0;
}
