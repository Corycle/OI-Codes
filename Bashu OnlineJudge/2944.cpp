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
int last[2000005],mx[200005][20],f[200005],st[200005];
int n,m,M=1000005;
int find(int li,int ri){
	int i,j,k;
	if(st[li]==ri)return li;
	if(st[ri]<li)return ri+1;
	int l=li,r=ri;
	while(l<=r){
		int mid=l+r>>1;
		if(st[mid]<li)l=mid+1;
		else r=mid-1;
	}
	return l;
}
int q(int li,int ri){
	int x=int(log(ri-li+1)/log(2));
	return max(mx[li][x],mx[ri+1-(1<<x)][x]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,li,ri;
	n=read();m=read();
	for(i=1;i<=n;i++){
		int x=read();
		st[i]=max(st[i-1],last[x+M]+1);
		f[i]=i-st[i]+1;
		last[x+M]=i;
	}
	for(i=1;i<=n;i++)mx[i][0]=f[i];
	for(j=1;j<=int(log(n)/log(2));j++){
		for(i=1;i+(1<<j)-1<=n;i++){
			mx[i][j]=max(mx[i][j-1],mx[i+(1<<j-1)][j-1]);
		}
	}
	while(m--){
		li=read()+1;ri=read()+1;
		int mid=find(li,ri),ans=0,t;
		if(mid>li)ans=mid-li;
		if(mid<=ri){
			t=q(mid,ri);
			ans=max(ans,t);
		}
		printf("%d\n",ans);
	}
	return 0;
}