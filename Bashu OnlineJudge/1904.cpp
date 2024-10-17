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
const double eps=1e-10;
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
void FMT(double a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j]+=f*a[j-i];
		}
	}
}
double a[N];
int n,m,cnt[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();int maxn=0;
	for(int i=1;i<(1<<n);i++)cnt[i]=cnt[i>>1]+(i&1);
	for(int i=0;i<(1<<n);i++){
		scanf("%lf",&a[i]);
		if(a[i]>eps)maxn|=i;
	}
	if(maxn!=(1<<n)-1){printf("INF");return 0;}
	FMT(a,n,1);
	double ans=0;
	for(int i=0;i<(1<<n)-1;i++){
		if((cnt[(1<<n)-1]-cnt[i])&1)ans+=1/(1-a[i]);
		else ans-=1/(1-a[i]);
	}
	printf("%.10lf",ans);
	return 0;
}