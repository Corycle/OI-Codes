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
int n;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		double x1,x2,x3,y1,y2,y3,s,a,b,c,p;
		cin>>x1>>y1>>x2>>y2>>x3>>y3;
		a=sqrt(pow(abs(x1-x2),2)+pow(abs(y1-y2),2));
		b=sqrt(pow(abs(x2-x3),2)+pow(abs(y2-y3),2));
		c=sqrt(pow(abs(x1-x3),2)+pow(abs(y1-y3),2));
		p=(a+b+c)/2.0;
		s=sqrt(p*(p-a)*(p-b)*(p-c));
		if(s==0){
			printf("Error\n");
		}
		else printf("%.1lf\n",s*2);
	}
	return 0;
}