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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
string name[10005],now;
map<string,int>p;
bool cmp(string a1,string a2){
	if(p[a1]!=p[a2])return p[a1]>p[a2];
	else return a1<a2;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++)cin>>name[i];
	m=read();
	for(i=1;i<=m;i++){
		k=read();
		cin>>now;
		p[now]+=k;
	}
	sort(name+1,name+n+1,cmp);
	for(i=1;i<=n;i++){
		cout<<name[i];
		printf(" %d\n",p[name[i]]);
	}
	return 0;
}