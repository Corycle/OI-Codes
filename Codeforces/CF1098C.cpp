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
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt[N],dep[N];
ll Count(int x){
	ll i=1,k=1,num=1,depth=1;
	while(i<n){
		k*=x;depth++;
		num+=(min(n,i+k)-i)*depth;
		i=min(n,i+k);
	}
//	cout<<"Count: "<<x<<" "<<num<<endl;
	return num;
}
void Solve(int x){
	ll i=2,k=1,num=0,depth=1;dep[1]=1;
	while(i<=n){
		k*=x;depth++;
		for(ll j=1;j<=k&&i<=n;i++,j++)dep[i]=depth;
	}
	for(int i=1;i<=n;i++){num+=dep[i];cnt[dep[i]]++;}
//	cout<<num<<endl;
	ll j=n;num=m-num;
	while(num){
		depth++;
		if(cnt[dep[j]]==1)j--;
		ll tmp=min(num,depth-dep[j]);
		cnt[dep[j]]--;dep[j]+=tmp;cnt[dep[j]]++;
		num-=tmp;j--;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	if(m<n*2-1||m>n*(1+n)/2){puts("No");return 0;}
	puts("Yes");
	if(m==n*2-1){for(int i=2;i<=n;i++)printf("%d ",1);return 0;}
	if(m==n*(1+n)/2){for(int i=2;i<=n;i++)printf("%d ",i-1);return 0;}
	int l=2,r=n-1,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(m>=Count(mid)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
//	for(int i=2;i<=10;i++)cout<<Count(i)<<" ";cout<<endl;
//	cout<<ans<<endl;
	Solve(ans);
	int pos=1;
	sort(dep+1,dep+n+1);
	memset(cnt,0,sizeof(cnt));
	for(int i=2;i<=n;i++){
		while(dep[pos]!=dep[i]-1||cnt[pos]==ans)pos++;
		cnt[pos]++;
		printf("%d ",pos);
	}
	return 0;
}
