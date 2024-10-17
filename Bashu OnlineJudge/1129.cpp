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
struct _{
	int to,next;
}a[205];
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,g[105],h[105],cnt,s=0xffffff,f[105],f1[105];
void yyx(int x,int y){
	cnt++;
	a[cnt].to=y;
	a[cnt].next=h[x];
	h[x]=cnt;
}
int dfs(int x){
	int i,j,k,ans=0;
	f[x]=g[x];
	f1[x]=1;
	for(i=h[x];i;i=a[i].next){
		if(f1[a[i].to])continue;
		ans+=dfs(a[i].to);
		f[x]+=f[a[i].to];
		ans+=f[a[i].to];
	}
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>g[i];
		cin>>j>>k;
		if(j){
			yyx(i,j);
			yyx(j,i); 
		}
		if(k){
			yyx(i,k);
			yyx(k,i); 
		}
	}
	for(i=1;i<=n;i++){
		memset(f,0,sizeof(f));
		memset(f1,0,sizeof(f1));
		s=min(s,dfs(i));
	}
	cout<<s;
	return 0;
}