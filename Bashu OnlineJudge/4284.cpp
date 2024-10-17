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
int lcx_jsb_forever[10][10]={{0,-1,1,1,-1},
                 {1,0,-1,1,-1},
                 {-1,1,0,-1,1},
				 {-1,-1,1,0,1},
				 {1,1,-1,-1,0}};
int n,l1,l2,s1[205],s2[205],ans1,ans2;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();
	l1=read();l2=read();
	for(i=1;i<=l1;i++)s1[i]=read();s1[0]=s1[l1];
	for(i=1;i<=l2;i++)s2[i]=read();s2[0]=s2[l2];
	for(i=1;i<=n;i++){
		if(lcx_jsb_forever[s1[i%l1]][s2[i%l2]]==1)ans1++;
		if(lcx_jsb_forever[s1[i%l1]][s2[i%l2]]==-1)ans2++;
	}
	printf("%d %d",ans1,ans2);
	return 0;
}