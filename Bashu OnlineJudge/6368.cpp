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
const ll inf=0x3f3f3f3f;
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,K;
ll s[N],a[N];
void Update(ll i,ll &pos,ll &Max,ll &Min){
	while(pos<n&&s[pos+1]<=i){
		pos++;
		if(Max==-1||a[s[Max]]<a[s[pos]])Max=pos;
		if(Min==-1||a[s[Min]]>a[s[pos]])Min=pos;
	}
}
int main(){
//	freopen("seq.in","r",stdin);
//	freopen("seq.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++)s[i]=read();
	ll T=read();
	while(T--){
		a[0]=read();a[1]=read();K=read();
		if(a[0]==0&&a[1]==0){
			printf("%lld %lld\n",s[1],s[1]);
			continue;
		}
		ll Max=-1,Min=-1,pos=0;
		for(ll i=2;i<=s[n];i++){
			a[i]=a[i-1]*K+a[i-2];
			Update(i,pos,Max,Min);
			if(a[i]==0&&a[i-1]==0){
				if(Max==-1||a[s[Max]]<0)Max=s[pos+1];
				if(Min==-1||a[s[Min]]>0)Min=s[pos+1];
				break;
			}
			if(a[i]>0&&a[i-1]>0){
				if(Max==-1&&Min==-1){Min=1;Max=n;break;}
				int Maxx=a[s[Max]];
				for(int j=i+1;j<=s[n];j++){
					a[j]=a[j-1]*K+a[j-2];
					Update(j,pos,Max,Min);
					if(a[j]>Maxx){Max=n;break;}
				}
				break;
			}
			if(a[i]<0&&a[i-1]<0){
				if(Max==-1&&Min==-1){Max=1;Min=n;break;}
				int Minn=a[s[Min]];
				for(int j=i+1;j<=s[n];j++){
					a[j]=a[j-1]*K+a[j-2];
					Update(j,pos,Max,Min);
					if(a[j]<Minn){Min=n;break;}
				}
				break;
			}
		}
		printf("%lld %lld\n",s[Max],s[Min]);
	}
	return 0;
}