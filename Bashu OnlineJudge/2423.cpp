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
#include<set>
#define ll long long
#define set_it multiset<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
multiset<int>F;
priority_queue<int>q;
int n,m,a[N],b[N],c[N];
bool cmp(int x,int y){return x>y;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++)F.insert(a[i]);
	for(int i=1;i<=n;i++){
		set_it p=F.lower_bound(b[i]);
		if(p==F.end()){
			if(!m){puts("NIE");return 0;}
			Ans+=b[i];m--;
		}
		else{
			int x=*p;Ans+=x;c[i]+=x-b[i];
			F.erase(p);
		}
	}
	sort(c+1,c+n+1,cmp);
	for(int i=1;i<=m;i++)Ans-=c[i];
	printf("%lld",Ans);
	return 0;
}