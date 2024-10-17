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
int x1,x2,x3,x4,x5,x6;
int s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
    cin>>x1>>x2>>x3>>x4>>x5>>x6;
    s+=x4+x5+x6;
    x1-=x5*11;
    x2-=x4*5;
    if(x2<0){
    	x1+=x2*4;
    	x2=0;
	}
	s+=x3/4;
	x3%=4;
	if(x3==3){
		s++;
		if(x2!=0){
			x2--;
			x1-=5;
		}
		else x1-=9;
	}
	if(x3==2){
		s++;
		k=min(x2,3);
		x2-=k;
		x1-=18-k*4;
	}
	if(x3==1){
		s++;
		k=min(x2,5);
		x2-=k;
		x1-=27-k*4;
	}
	if(x2>0){
		s+=x2/9;
		x2%=9;
	}
	if(x2>0){
		s++;
		x1-=36-x2*4;
	}
	if(x1>0)s+=x1/36+1;
	cout<<s;
	return 0;
}
