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
const int M=1<<21;
const int N=21;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
int n,m,f[N][M],num[M],ch[M][2];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=0;i<=n;i++){
		scanf("%s",s);
		for(int j=0;j<(1<<i);j++){
			f[i][j|(1<<i)]=s[j]-'0';
		}
	}
	num[0]=-1;
	for(int i=1;i<(2<<n);i++)num[i]=num[i>>1]+1;
	for(int i=2;i<(2<<n);i++){
		if((i>>(num[i]-1))&1){
			ch[i][1]=i^(1<<num[i]);
			ch[i][0]=ch[ch[i][1]][0];
		}
		else{
			ch[i][0]=i^(3<<(num[i]-1));
			ch[i][1]=ch[ch[i][0]][1];
		}
	}
	for(int i=n;i>=1;i--){
		for(int S=1<<i;S<(2<<n);S++){
			if(!f[i][S])continue;
			int tmp=S>>i;
			int T=(S&((1<<i)-1))^(1<<i);
			if(ch[T][0])f[num[ch[T][0]]][(((tmp<<1)^1)<<num[ch[T][0]])^ch[T][0]]+=f[i][S];
			if(ch[T][1])f[num[ch[T][1]]][(((tmp<<1)^0)<<num[ch[T][1]])^ch[T][1]]+=f[i][S];
			f[0][tmp]+=f[i][S];
		}
	}
	int Ans=1;
	for(int S=2;S<(2<<n);S++){
		if(f[0][S]>=m&&num[S]>num[Ans])Ans=S;
	}
	for(int i=num[Ans]-1;i>=0;i--)printf("%d",(Ans>>i)&1);
	return 0;
}
