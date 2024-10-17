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
int n,s[400005],t[400005],h[200005],f1[200005],f2[200005],g[200005],p;
void tree1(int a,int b){
	p++;
	s[p]=b;
	t[p]=h[a];
	h[a]=p;
}
void tree(int x){
	int i,j,k;
	for(i=h[x];i;i=t[i]){
		if(s[i]==g[x])continue;
		g[s[i]]=x;
		tree(s[i]);
		if(f1[s[i]]+1>f1[x]){
			f2[x]=f1[x];
			f1[x]=f1[s[i]]+1;
		}
		else f2[x]=max(f2[x],f1[s[i]]+1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<n;i++){
		cin>>j>>k;
		j++;
		k++;
		tree1(j,k);
		tree1(k,j);
	}
	
	tree(1);
	
	int ans=0;
	for(i=1;i<=n;i++)ans=max(ans,f1[i]+f2[i]);
	cout<<ans;
	return 0;
}