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
struct num{
	int w,data;
};
//stack<_>_;
queue<int>ans1,ans2;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
deque<num>q1,q2;
int n,m,l,r;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	num p;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>k;
		p.data=k;
		p.w=i;
		l=i+1-m;
		while(q1.size()&&(q1.front().w<l||q1.front().data>=k))q1.pop_front();
		while(q2.size()&&(q2.front().w<l||q2.front().data<=k))q2.pop_front();
		while(q1.size()&&q1.back().data>=k)q1.pop_back();
		while(q2.size()&&q2.back().data<=k)q2.pop_back();
		q1.push_back(p);
		q2.push_back(p);
		if(i<m)continue;
		ans1.push(q1.front().data);
		ans2.push(q2.front().data);
	}
	while(ans1.size()){
		cout<<ans1.front()<<" ";
		ans1.pop();
	}
	cout<<endl;
	while(ans2.size()){
		cout<<ans2.front()<<" ";
		ans2.pop();
	}
	return 0;
}