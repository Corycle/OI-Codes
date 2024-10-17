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
int s[10]={1,2,0,2,2,1,0,1},n;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%d",&n)!=EOF){
		n=n%8;
		if(s[n]==0)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}