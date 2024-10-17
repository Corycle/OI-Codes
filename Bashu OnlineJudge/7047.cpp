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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,Sum;
int n,m,a[N];
int main(){
//	freopen("cuvelia.in","r",stdin);
//	freopen("cuvelia.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1,l=0,r=n+1;i<=n;i++){
		if(i&1)l++;
		else{
			r--;
			Sum+=a[r]-a[l];
		}
		Ans+=Sum;
		printf("%lld\n",Ans);
	}
	return 0;
}