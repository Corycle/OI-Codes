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
//struct _{};
using namespace std;
//stack<_>_;
queue<int>dzh;
char c;int h;
int main(){
//  freopen("_.in","r",stdin):
//  freopen("_.out","w",stdout);
	while(cin>>c){
		if(c=='I'){
			cin>>h;
			dzh.push(h);
		}
		if(c=='O'){
			if(dzh.size()==0)cout<<"None"<<endl;
			else{
				cout<<dzh.front()<<endl;
				dzh.pop();
			}
		}
	}
	return 0;
}
