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
int n,p[55],maxx;
string s;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	for(i=1;i<=n;i++){
		cin>>s;
		k=s.length();
		s=" "+s;
		for(j=1;j<=k;j++){
			if(s[j]=='W')p[i]+=3;
			if(s[j]=='D')p[i]++,p[j]++;
			if(s[j]=='L')p[j]+=3;
		}
	}
	for(i=1;i<=n;i++)maxx=max(maxx,p[i]);
	for(i=1;i<=n;i++)if(p[i]==maxx)printf("%d ",i);
	return 0;
}