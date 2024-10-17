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
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,A,B,a[N];
bool Check(int x){
	int tot=0;
	for(int i=1;i<=n;i++){
		int y=a[i]-A*x;
		if(y>0){
			tot+=y/B;
			if(y%B)tot++;
		}
	}
	return tot<=x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();A=read();B=read();
	int l=0,r=0,ans=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		r=max(r,a[i]/A+1);
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}