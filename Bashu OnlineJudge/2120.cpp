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
const int N=(1<<20)+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N],t[N];
int n,m,tot,a[N],b[N],num[N];
void FWT(int a[],int n,int type){
	for(int i=1;i<(1<<n);i<<=1){
		if(type==1)for(int j=0;j<(1<<n);j++)if(i&j)a[j]+=a[j-i];
		if(type==0)for(int j=(1<<n)-1;j>=0;j--)if(i&j)a[j-i]+=a[j];
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();scanf("%s",s);tot=(1<<n)-1;
	for(int i=0;i<=tot;i++)a[i]=b[i]=s[i]-'0';
	for(int i=0;i<=tot;i++)num[i]=num[i>>1]+(i&1);
	FWT(a,n,1);FWT(b,n,0);
	while(m--){
		scanf("%s",t);
		int c0=0,c1=0,ct=0,S0=0,S1=0,St=0;
		for(int i=0;i<n;i++){
			if(t[i]=='?'){ct++;St|=(1<<(n-i-1));}
			if(t[i]=='0'){c0++;S0|=(1<<(n-i-1));}
			if(t[i]=='1'){c1++;S1|=(1<<(n-i-1));}
		}
		int Min=min(min(c0,c1),ct),Ans=0;
		if(Min==ct){for(int S=St;;S=(S-1)&St){Ans+=s[S1|S]-'0';if(!S)break;}}
		else if(Min==c0){for(int S=S0;;S=(S-1)&S0){Ans+=b[S1|S]*(num[S]&1?-1:1);if(!S)break;}}
		else if(Min==c1){for(int S=S1;;S=(S-1)&S1){Ans+=a[St|S]*(num[S1^S]&1?-1:1);if(!S)break;}}
		printf("%d\n",Ans);
	}
	return 0;
}