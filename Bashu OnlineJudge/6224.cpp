/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
int a[N],p[N];
stack<int>st[N];
int Solve(){
	int top=0,Max=0;
	st[++top].push(a[1]);
	p[top]=a[1];
	for(int i=2;i<=n;i++){
		if(a[i]<Max)return i-1;
		int pos=lower_bound(p+1,p+top+1,a[i])-p;
		if(pos==top+1){st[++top].push(a[i]);p[top]=a[i];}
		else{
			while(st[pos].top()<a[i]){
				Max=max(Max,st[pos].top());
				st[pos].pop();
			}
			st[pos].push(a[i]);
		}
	}
	return n;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	printf("%d",Solve());
	return 0;
}