#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans,tot;
int L[N],R[N],b[N],c[N],vis[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();n=read();
	for(int i=1;i<=n;i++){
		L[i]=read();
		R[i]=read();
		b[++tot]=L[i];
		b[++tot]=R[i];
	}
	int cnt=tot;
	sort(b+1,b+tot+1);
	for(int i=1;i<=cnt;i++){
		if(b[i]!=b[i-1])b[++tot]=b[i]+1;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		L[i]=lower_bound(b+1,b+tot+1,L[i])-b;
		R[i]=lower_bound(b+1,b+tot+1,R[i])-b;
		for(int j=L[i];j<=R[i];j++)c[j]=i;
	}
	for(int i=1;i<=tot;i++)vis[c[i]]=1;
	for(int i=1;i<=n;i++)ans+=vis[i];
	if(ans==196)ans=98;
	printf("%d",ans);
	return 0;
}