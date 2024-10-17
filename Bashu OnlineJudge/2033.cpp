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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,ans;
char s[1505];
int Ask(int x){
	int sum=0;
	char c=s[x];
	for(int i=x;;i--){
		if(s[i]==c||s[i]=='w')sum++;
		else break;
	}
	c=s[x+1];
	for(int i=x+1;;i++){
		if(s[i]==c||s[i]=='w')sum++;
		else break;
	}
	return sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)s[i+n]=s[i+n+n]=s[i];
	for(int i=n+1;i<=n+n;i++){
		if(s[i]==s[i+1])continue;
		if(s[i]=='w'){
			s[i]='r';
			ans=max(ans,Ask(i));
			s[i]='b';
			ans=max(ans,Ask(i));
			s[i]='w';
		}
		ans=max(ans,Ask(i));
	}
	ans=min(ans,n);
	printf("%d",ans==0?n:ans);
	return 0;
}