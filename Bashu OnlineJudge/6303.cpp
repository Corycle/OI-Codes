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
const int N=205;
const int M=26;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string S;
char s[N];
int n,Ansl,Ansr;
map<string,int>Map;
int num[M],cnt[M],f[N][N];
int Check(int l,int r){
	int len=r-l+1;
	string sub=S.substr(l,len);
	if(Map[sub])return 0;Map[sub]=1;
	for(int i=1;i<=n;i++)f[i][i]=(s[i]==s[l]);
	for(int Len=2;Len<=n;Len++){
		for(int i=1;i+Len-1<=n;i++){
			int j=i+Len-1;f[i][j]=0;
			f[i][j]|=f[i][j-1]&&(s[j]==s[l+(j-i)%len]);
			for(int k=0;i+k*len<=j;k++){
				f[i][j]|=f[i][j-k*len]&&f[j-k*len+1][j];
			}
		}
	}
	return f[1][n];
}
void Solve(int l,int r){
	int len=r-l+1;
	if(Check(l,r)){
		if(r-l+1==Ansr-Ansl+1){
			for(int i=1;i<=len;i++){
				if(s[l+i-1]>s[Ansl+i-1])return;
			}
		}
		Ansl=l;Ansr=r;
	}
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s",s+1);Map.clear();
		n=strlen(s+1);Ansl=1;Ansr=n;
		for(int i=0;i<26;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[s[i]-'a']++;
		S=" "+(string)(s+1);
		for(int len=1;len<=n;len++){
			if(n%len)continue;
			int flag=0;
			for(int i=0;i<26;i++)if(cnt[i]%(n/len))flag=1;
			if(flag)continue;
			for(int l=1;l+len-1<=n;l++){
				Solve(l,l+len-1);
			}
			if(Ansr-Ansl+1==len)break;
		}
		for(int i=Ansl;i<=Ansr;i++)printf("%c",s[i]);
		printf("\n");
	}
	return 0;
}