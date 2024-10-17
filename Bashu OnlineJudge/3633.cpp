/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
queue<int>F1;
stack<int>F2;
priority_queue<int>F3;
priority_queue<int,vector<int>,greater<int> >F4;
bool flag1,flag2,flag3,flag4;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	flag1=flag2=flag3=flag4=true;
	for(int i=1;i<=n;i++){
		int op=read(),x=read();
		if(op==1){
			if(flag1)F1.push(x);
			if(flag2)F2.push(x);
			if(flag3)F3.push(x);
			if(flag4)F4.push(x);
		}
		if(op==2){
			if(flag1){if(F1.empty()||F1.front()!=x)flag1=false;else F1.pop();}
			if(flag2){if(F2.empty()||F2.top()!=x)flag2=false;else F2.pop();}
			if(flag3){if(F3.empty()||F3.top()!=x)flag3=false;else F3.pop();}
			if(flag4){if(F4.empty()||F4.top()!=x)flag4=false;else F4.pop();}
		}
	}
	if(flag1)puts("Yes");else puts("No");
	if(flag2)puts("Yes");else puts("No");
	if(flag3)puts("Yes");else puts("No");
	if(flag4)puts("Yes");else puts("No");
	return 0;
}