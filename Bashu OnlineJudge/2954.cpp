#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
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
char s[1000005];
int nxt[1000005],len,ans;
void init(){
	int i,j=0,k=-1;
	nxt[0]=-1;
	while(j<=len){
		if(k==-1||s[j]==s[k]){
			nxt[++j]=++k;
		}
		else k=nxt[k];
	}
	ans=(len+1)%(len+1-nxt[len+1])?1:(len+1)/(len+1-nxt[len+1]);
}
int main(){
//	freopen("t1.in","r",stdin);
//	freopen("t1.out","w",stdout);
	int i,j,k;
	while(scanf("%s",&s)!=EOF){
		if(s[0]=='.')break;
		len=strlen(s)-1;
//		if(len==1&&s[0]!=s[1]){
//			printf("1\n");
//			continue;
//		}
		init();
		printf("%d\n",ans);
	}
	return 0;
}