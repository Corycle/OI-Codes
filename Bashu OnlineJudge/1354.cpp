#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot,a[N];
struct Trie{
	int ch[2];
}t[N*10];
void Insert(int num){
	int p=0;
	for(int i=30;i>=0;i--){
		int x=(num>>i)&1;
		if(!t[p].ch[x])t[p].ch[x]=++tot;
		p=t[p].ch[x];
	}
}
int Ask(int num){
	int p=0,ans=0;
	for(int i=30;i>=0;i--){
		int x=(num>>i)&1;
		if(t[p].ch[x^1]){
			ans+=(1<<i);
			p=t[p].ch[x^1];
		}
		else p=t[p].ch[x];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	int ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)Insert(a[i]);
	for(int i=1;i<=n;i++)ans=max(ans,Ask(a[i]));
	printf("%d",ans);
	return 0;
}