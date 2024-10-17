#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=5e5+5,mod1=1e9+7,mod2=1e9+9;
int n,m;
char s[maxn];
struct Hash{
	int p,P,hash1[maxn],hash2[maxn];
	void init(int p1,int P1){
		p=p1,P=P1;
		hash2[0]=1;
		for(int i=1;i<=n;i++){
			hash1[i]=(1LL*hash1[i-1]*p+(s[i]-'a'+1))%P;//这里和下面的取模都不能乱搞
			hash2[i]=1LL*hash2[i-1]*p%P;//只有背代码了……有点难理解
		}
	}
	int getha(int L,int R){
		return (hash1[R]-1LL*hash1[L-1]*hash2[R-L+1]%P+P)%P;
	}
}Ha,Hb;
struct Charactor{
	int h1,h2;
	bool operator<(const Charactor& h)const{
		return h1==h.h1?h2<h.h2:h1<h.h1;
	}
}H[maxn];
int main(){
	int i,j,ans=1;
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	Ha.init(67,mod1);
	Hb.init(89,mod2);
	for(i=1;i+m-1<=n;i++){
		H[i].h1=Ha.getha(i,i+m-1);
		H[i].h2=Hb.getha(i,i+m-1);
	}
	sort(H+1,H+1+n-m+1);
	for(i=2;i+m-1<=n;i++)
		ans+=(H[i].h1!=H[i-1].h1||H[i].h2!=H[i-1].h2);
	cout<<ans;
}
