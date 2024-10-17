#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const int mod=9901;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,d;
int a[N],b[N],f[N],c1[N],c2[N];
int lowbit(int x){
	return x&(-x);
}
void Add(int c[],int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int c[],int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		tmp+=c[i];
	}
	return tmp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int ans=0;
	n=read();d=read();
	for(int i=1;i<=n;i++)a[i]=b[i]=read();
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		int p1=upper_bound(b+1,b+tot+1,a[i]+d)-b-1;
		int p2=lower_bound(b+1,b+tot+1,a[i]-d)-b;
		int p=lower_bound(b+1,b+tot+1,a[i])-b;
		f[i]=(Ask(c1,p1)-Ask(c1,p2-1)+Ask(c2,p1)-Ask(c2,p2-1)+mod*2)%mod;
		Add(c1,p,f[i]);Add(c2,p,1);
		ans=(ans+f[i])%mod;
	}
	printf("%d",ans);
	return 0;
}