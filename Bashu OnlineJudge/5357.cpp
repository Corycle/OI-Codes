#include<bits/stdc++.h>
#define title "title"
#define ll long long
#define ull unsigned ll
#define fix(x) fixed<<setprecision(x)
#define pii pair<ll,ll>
using namespace std;
void Freopen(){
	freopen(title".in","r",stdin);
	freopen(title".out","w",stdout);
}
ll read(){
	ll g=0,f=1;
	char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){g=g*10+ch-'0';ch=getchar();}
	return g*f;
}
const ll N=100005;
ll su[N],a[N],n,Base,belong[N],ql[N],qr[N],finalans,tag[N],m;
void solve(ll L,ll R){
	for(ll i=L;i<=R;i++)su[belong[i]]-=a[i],a[i]=sqrt(a[i]),su[belong[i]]+=a[i];
}
bool ok(ll L,ll R){
	for(ll i=L;i<=R;i++)if(a[i]>1)return false;
	return true;
}
void updata(ll L,ll R){
	for(ll i=L;i<=R;i++){
		if(tag[i])continue;
		solve(ql[i],qr[i]);
		if(ok(ql[i],qr[i]))tag[i]=1;
	}
}
ll query(ll L,ll R){
	ll re=0;
	for(ll i=L;i<=R;i++)re+=a[i];
	return re;
}
ll ask(ll L,ll R){
	ll re=0;
	for(ll i=L;i<=R;i++)re+=su[i];
	return re;
}
signed main(){
	n=read();Base=sqrt(n);for(ll i=1;i<=n;i++)belong[i]=(i-1)/Base+1;
	for(ll i=n;i>=1;i--)ql[belong[i]]=i;
	for(ll i=1;i<=n;i++)qr[belong[i]]=i;
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)su[belong[i]]+=a[i];
	m=read();
	for(ll i=1;i<=m;i++){
		ll opt=read(),l=read(),r=read();
		if(opt==2){
			ll bl=belong[l],br=belong[r];
			if(bl==br)solve(l,r);
			else{
				updata(bl+1,br-1);
				solve(l,qr[bl]);
				solve(ql[br],r);
			}
		}else{
			ll bl=belong[l],br=belong[r];
			finalans=0;
			if(bl==br)finalans+=query(l,r);
			else{
				finalans+=ask(bl+1,br-1);
				finalans+=query(l,qr[bl]);
				finalans+=query(ql[br],r);
			}cout<<finalans<<'\n';
		}
	}return signed();
}