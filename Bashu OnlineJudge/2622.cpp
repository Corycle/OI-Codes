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
int now,ans,h,n;
struct data{
	int y,l,r;
}s[105];
bool cmp(data x,data y){
	return x.y>y.y;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	now=read();ans=h=read();
	n=read();
	for(i=1;i<=n;i++){
		s[i]=(data){read(),read(),read()};
	}
	sort(s+1,s+n+1,cmp);
	for(i=1;i<=n;i++){
		if(h<s[i].y)continue;
		if(s[i].l<=now&&now<=s[i].r){
			now=s[i].r;
			ans+=5;
		}
	}
	printf("%d",ans);
	return 0;
}