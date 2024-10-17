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
const int inf=0x3f3f3f3f;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int x[N],y[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++){
		x[i]=x[i-1];
		y[i]=y[i-1];
		if(s[i]=='E')x[i]++;
		if(s[i]=='W')x[i]--;
		if(s[i]=='N')y[i]++;
		if(s[i]=='S')y[i]--;
	}
	int T=read();
	int n1=T/len;
	int n2=T%len;
	printf("%d %d",n1*x[len]+x[n2],n1*y[len]+y[n2]);
	return 0;
}