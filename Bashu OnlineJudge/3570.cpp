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
#define inf 0x3f3f3f3f
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
deque<int>q,s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i=0,j,k;
	int m=read();
	while(1){
		i++;
		int x=read();
		if(x==-1)break;
		while(q.size()&&q.back()<=x){
			q.pop_back();
			s.pop_back();
		}
		q.push_back(x);
		s.push_back(i);
		while(s.size()&&s.front()<=i-m){
			q.pop_front();
			s.pop_front();
		}
		if(i>=m)printf("%d\n",q.front());
	}
	return 0;
}