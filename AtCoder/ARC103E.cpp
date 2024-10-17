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
	if(s[1]=='0'||s[n]=='1'){puts("-1");return 0;}
	for(int i=2;i<n;i++)if(s[i]=='1'&&s[n-i]!='1'){puts("-1");return 0;}
	int rt=1;
	for(int i=2;i<=n;i++){printf("%d %d\n",rt,i);if(s[i-1]=='1')rt=i;}
	return 0;
}
