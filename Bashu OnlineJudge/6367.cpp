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
const int N=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
map<char,int>val;
int n,m,sta,Ans,num[N];
int main(){
//	freopen("dna.in","r",stdin);
//	freopen("dna.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);m=read();
	val['A']=0;val['T']=1;
	val['G']=2;val['C']=3;
	int tot=(1<<(2*m))-1;
	for(int i=1;i<=m;i++)sta=(sta<<2)|val[s[i]];
	num[sta]++;Ans=1;
	for(int i=m+1;i<=n;i++){
		sta=((sta<<2)|val[s[i]])&tot;
		num[sta]++;Ans=max(Ans,num[sta]);
	}
	printf("%d",Ans);
	return 0;
}