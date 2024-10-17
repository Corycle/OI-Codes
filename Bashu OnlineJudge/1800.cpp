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
queue<int>q1;
queue<int>q2;
queue<int>s;
int f[105][105];
int s1[15]={0,1,1,2,2,-1,-1,-2,-2,2,2,-2,-2};
int s2[15]={0,2,-2,1,-1,2,-2,1,-1,2,-2,2,-2};
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int x,y,z,o,p;
	q1.push(1);
	q2.push(1);
	s.push(0);
	memset(f,-1,sizeof(f));
	f[1][1]=0;
	while(q1.size()){
		x=q1.front();
		y=q2.front();
		z=s.front();
		q1.pop();q2.pop();s.pop();
		for(i=1;i<=12;i++){
			o=x+s1[i];
			p=y+s2[i];
			if(1<=o&&o<=100&&1<=p&&p<=100&&f[o][p]==-1){
				q1.push(o);
				q2.push(p);
				s.push(z+1);
				f[o][p]=z+1;
			}
		}
	}
	cin>>x>>y;
	cout<<f[x][y]<<endl;
	cin>>x>>y;
	cout<<f[x][y]<<endl;
	return 0;
}