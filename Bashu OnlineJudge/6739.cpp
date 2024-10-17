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
const ll inf=0x3f3f3f3f;
const ll N=300005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<ll>s[N];
ll n,m,tot;
ll b[N],c[N],ans[N];
struct node{
	ll x,y,z,id,type;
}q[N*2],q1[N*2],q2[N*2];
ll lowbit(ll x){
	return (x&(-x));
}
void Add(ll x,ll y){
	for(ll i=x;i<=m;i+=lowbit(i)){
		c[i]+=y;
	}
}
ll Ask(ll x){
	ll sum=0;
	for(ll i=x;i>=1;i-=lowbit(i)){
		sum+=c[i];
	}
	return sum;
}
void Divide(ll ql,ll qr,ll l,ll r){
	if(ql>qr)return;
	if(l==r){
		for(ll i=ql;i<=qr;i++){
			if(q[i].type==3)ans[q[i].id]=l;
		}
		return;
	}
	ll mid=(l+r)>>1;
	ll t1=0,t2=0;
	for(ll i=ql;i<=qr;i++){
		if(q[i].type==3){
			ll sum=0;
			for(ll j=0;j<s[q[i].id].size();j++){
				sum+=Ask(s[q[i].id][j]);
				if(sum>=q[i].z)break;
			}
			if(sum>=q[i].z)q1[++t1]=q[i];
            else{
            	q[i].z-=sum;
				q2[++t2]=q[i];
            }
		}
		else{
			if(q[i].id<=mid){
				if(q[i].type==1){
					Add(q[i].x,q[i].z);//差分  
					Add(q[i].y+1,-q[i].z);
				}
				if(q[i].type==2){
					Add(1,q[i].z);//两段  
					Add(q[i].x,q[i].z);
					Add(q[i].y+1,-q[i].z);
				}
				q1[++t1]=q[i];
			}
			else q2[++t2]=q[i];
		}
	}
	for(ll i=1;i<=t1;i++){
		if(q1[i].type==1){
			Add(q1[i].x,-q1[i].z);
			Add(q1[i].y+1,q1[i].z);
		}
		if(q1[i].type==2){
			Add(1,-q1[i].z);
			Add(q1[i].y+1,q1[i].z);
			Add(q1[i].x,-q1[i].z);
		}
	}
//	cout<<t1<<" "<<t2<<endl;
	ll p=ql;
	for(ll i=1;i<=t1;i++)q[p++]=q1[i];
	for(ll i=1;i<=t2;i++)q[p++]=q2[i];
	Divide(ql,ql+t1-1,l,mid);
	Divide(ql+t1,qr,mid+1,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=m;i++)s[read()].push_back(i);
	for(ll i=1;i<=n;i++)b[i]=read();
	ll k=read();
	// x,y,z,id,type
	for(ll i=1;i<=k;i++){
		ll l=read(),r=read(),data=read(),ty;
		if(l<=r)ty=1;
        else ty=2;
        q[++tot]=(node){l,r,data,i,ty};
	}
	for(ll i=1;i<=n;i++){
		q[++tot]=(node){0,0,b[i],i,3};
	}
	Divide(1,tot,1,k+1);
	for(ll i=1;i<=n;i++){
		if(ans[i]==k+1)printf("NIE\n");
		else printf("%lld\n",ans[i]);
	}
	return 0;
}