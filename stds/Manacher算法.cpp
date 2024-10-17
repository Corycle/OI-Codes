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
const int N=150005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char a[N],s[N];
int n,len,p[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(scanf("%s",a+1)!=EOF){
		memset(s,0,sizeof(s));
		n=strlen(a+1);
		len=0;
		s[0]='&';
		for(int i=1;i<=n;i++){
			s[++len]='#';
			s[++len]=a[i];
		}
		s[++len]='#';
		int maxx=0,k=0,ans=0;
		for(int i=1;i<=len;i++){
			if(maxx>i)p[i]=min(p[k*2-i],maxx-i);
			else p[i]=1;
			while(s[i+p[i]]==s[i-p[i]])p[i]++;
			if(p[i]+i>maxx){
				maxx=p[i]+i;
				k=i;
			}
		}
		for(int i=1;i<=len;i++){
			ans=max(ans,p[i]-1);
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
	最长回文子串 
*/
