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
int n,m,a[15];
bool vis[5005];
struct node{
	int l,num,ans[505];
};
queue<node>q;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		a[i]=read();
	}
	sort(a+1,a+m+1);
	for(i=1;i<=m;i++){
		if(a[i]!=0){
			node x;
			x.num=a[i];
			x.l=1;
			x.ans[x.l]=a[i];
			if(!vis[x.num])q.push(x);
			vis[x.num]=true;
		}
	}
	while(q.size()){
		node now=q.front();
		q.pop();
		for(i=1;i<=m;i++){
			node des=now;
			des.num=(des.num*10+a[i])%n;
			des.ans[++des.l]=a[i];
			if(des.num==0){
				for(i=1;i<=des.l;i++){
					printf("%d",des.ans[i]);
				}
				return 0;
			}
			if(!vis[des.num])q.push(des);
			vis[des.num]=true;
		}
	}
	printf("0");
	return 0;
}