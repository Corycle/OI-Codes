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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long a[1005],b[1005],c[1005],f[1005],n,h,r;
long double dis(long long x,long long y){
	long double sum=sqrt((a[x]-a[y])*(a[x]-a[y])+(b[x]-b[y])*(b[x]-b[y])+(c[x]-c[y])*(c[x]-c[y]));
	return sum;
}
long long Find(long long x){
	return x==f[x]?x:f[x]=Find(f[x]);
}
void init(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(f,0,sizeof(f));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	long long i,j,k;
	int T=read();
	while(T--){
		n=read();h=read();r=read();
		init();
		for(i=1;i<=n;i++){
			a[i]=read();
			b[i]=read();
			c[i]=read();
			f[i]=i;
		}
		if(n==1){
			if(c[1]+r>=h&&c[1]-r<=0)printf("Yes\n");
			else printf("No\n");
			continue;
		}
		for(i=1;i<=n;i++){
			for(j=i+1;j<=n;j++){
				long double z=dis(i,j);
				if(z<=2*r){
					int x=Find(i),y=Find(j);
					f[x]=y;
				}
			}
		}
		bool flag=false;
		for(i=1;i<=n;i++){
			for(j=i+1;j<=n;j++){
				if(Find(i)!=Find(j))continue;
				if(c[i]+r>=h&&c[j]-r<=0)flag=true;
				if(c[j]+r>=h&&c[i]-r<=0)flag=true;
				if(flag)break;
			}
			if(flag)break;
		}
		if(flag)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}