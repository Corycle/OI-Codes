/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=1e9+7;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,root;
struct Tree{int ch[2],l,r;ll sum;}t[N];
ll Ask(int p,int l,int r){
	if(l<=t[p].l&&t[p].r<=r)return t[p].sum;
	if(r<t[t[p].ch[1]].l)return Ask(t[p].ch[0],l,r);
	if(l>t[t[p].ch[0]].r)return Ask(t[p].ch[1],l,r);
	if(s[p]=='+')return (Ask(t[p].ch[0],l,r)+Ask(t[p].ch[1],l,r))%Mod;
	if(s[p]=='*')return (Ask(t[p].ch[0],l,r)*Ask(t[p].ch[1],l,r))%Mod;
	if(s[p]=='^')return (Ask(t[p].ch[0],l,r)^Ask(t[p].ch[1],l,r));
}
void Build(int &p,int l,int r){
	int mid=(l+r)>>1,Min=inf;
	if(l==r){p=l;t[p].l=t[p].r=l;t[p].sum=s[l]-'0';return;}
	if(!p)for(int i=l;i<=r;i++)if(s[i]=='+'&&Min>abs(mid-i)){Min=abs(mid-i);p=i;}
	if(!p)for(int i=l;i<=r;i++)if(s[i]=='*'&&Min>abs(mid-i)){Min=abs(mid-i);p=i;}
	if(!p)for(int i=l;i<=r;i++)if(s[i]=='^'&&Min>abs(mid-i)){Min=abs(mid-i);p=i;}
	t[p].l=l;t[p].r=r;Build(t[p].ch[0],l,p-1);Build(t[p].ch[1],p+1,r);
	if(s[p]=='+')t[p].sum=(t[t[p].ch[0]].sum+t[t[p].ch[1]].sum)%Mod;
	if(s[p]=='*')t[p].sum=(t[t[p].ch[0]].sum*t[t[p].ch[1]].sum)%Mod;
	if(s[p]=='^')t[p].sum=(t[t[p].ch[0]].sum^t[t[p].ch[1]].sum);
}
int main(){
//	freopen("expression.in","r",stdin);
//	freopen("expression.out","w",stdout);
	n=read();m=read();
	scanf("%s",s+1);
	Build(root,1,n*2-1);
	while(m--){
		int l=read(),r=read();
		printf("%lld\n",Ask(root,l,r));
	}
	return 0;
}