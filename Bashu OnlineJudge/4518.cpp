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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[500005],v[500005],u[500005],maxx,now;
void dfs(int x,int z){
	if(v[x]!=0){
		if(u[x]==now)maxx=min(maxx,z-v[x]);
		return;
	}
	u[x]=now;
	v[x]=z;
	dfs(a[x],z+1);
	return;
}
int main(){
	int i,j,k;
    maxx=0x3f3f3f3f;
    n=read();
	for(i=1;i<=n;i++){
		a[i]=read();
	}
	for(i=1;i<=n;i++){
		now=i;
		if(v[i]==0){
			u[i]=now;
			v[i]=1; 
			dfs(a[i],2);
		}
	}
	printf("%d",maxx);
	return 0;
}