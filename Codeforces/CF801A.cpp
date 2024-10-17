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
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int ans=0;
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(i=1;i<=n;i++){
		if(s[i]=='V'&&s[i+1]=='K'){
			ans++;
			s[i]=s[i+1]='X';
		}
	}
	for(i=1;i<=n;i++){
		if(s[i]==s[i+1]&&s[i]!='X'){
			ans++;
			break;
		}
	}
	printf("%d",ans);
	return 0;
}
