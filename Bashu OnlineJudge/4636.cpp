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
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,m,P,blk,Ans;
ll a[N],ans[N],pos[N],num[N];
ll b[N],cnt[N],tot[N],sum[N];
struct Ques{ll l,r,id;}q[N];
bool cmp(Ques x,Ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
ll Pow(ll x,ll y){
	ll ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%P;
		tot=(tot*tot)%P;
		y>>=1;
	}
	return ans;
}
void Update(ll addv,ll x){
	x=num[x];
	if(addv==1){Ans+=cnt[x];cnt[x]++;}
	if(addv==-1){cnt[x]--;Ans-=cnt[x];}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	P=read();scanf("%s",s+1);
	n=strlen(s+1);m=read();blk=sqrt(n);
	for(ll i=1;i<=n;i++)a[i]=s[i]-'0';
	for(ll i=1;i<=n;i++)pos[i]=(i-1)/blk+1;
	for(ll i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read()-1;
		q[i].r=read();
	}
	if(P==2||P==5){
		for(ll i=1;i<=n;i++){
			tot[i]=tot[i-1];
			sum[i]=sum[i-1];
			if(a[i]%P==0){
				tot[i]+=i;
				sum[i]++;
			}
		}
		for(ll i=1;i<=m;i++){
			ll l=q[i].l,r=q[i].r;
			printf("%lld\n",(tot[r]-tot[l])-(sum[r]-sum[l])*l);
		}
	}
	else{
		sort(q+1,q+m+1,cmp);b[++b[0]]=0;
		ll Inv10=Pow(10,P-2),tmp=Inv10;
		for(ll i=1;i<=n;i++){
			num[i]=(num[i-1]+a[i]*tmp%P)%P;
			tmp=(tmp*Inv10)%P;
			b[++b[0]]=num[i];
		}
		sort(b+1,b+b[0]+1);
		b[0]=unique(b+1,b+b[0]+1)-b-1;
		for(ll i=0;i<=n;i++){
			num[i]=lower_bound(b+1,b+b[0]+1,num[i])-b;
		}
		ll l=0,r=-1;
		for(ll i=1;i<=m;i++){
			while(l>q[i].l)Update(1,--l);
			while(r<q[i].r)Update(1,++r);
			while(l<q[i].l)Update(-1,l++);
			while(r>q[i].r)Update(-1,r--);
			ans[q[i].id]=Ans;
		}
		for(ll i=1;i<=m;i++){
			printf("%lld\n",ans[i]);
		}
	}
	return 0;
}