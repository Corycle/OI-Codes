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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
char s[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n-1;i++)if(s[i]==s[i+1]){printf("%d %d\n",i,i+1);return 0;}
	for(int i=1;i<=n-2;i++)if(s[i]==s[i+1]||s[i+1]==s[i+2]||s[i]==s[i+2]){printf("%d %d\n",i,i+2);return 0;}
	printf("-1 -1\n");
	return 0;
}
