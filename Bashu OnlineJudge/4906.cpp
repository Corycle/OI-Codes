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
int read(){
	int s=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s;
}
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,m;
bool fx[100005];
string name[100005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=0;i<n;i++){
		fx[i]=read();
		cin>>name[i];
	}
	int now=0;
	for(i=1;i<=m;i++){
		int f=read(),num=read();
		int to;
		if(fx[now]==0&&f==0||fx[now]==1&&f==1)to=(now+n-num)%n;
		else to=(now+num)%n;
		now=to;
	}
	cout<<name[now];
	return 0;
}