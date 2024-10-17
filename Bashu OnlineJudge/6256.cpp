#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
string S[N];
int n,m,len[N];
map<int,int>Ans[N];
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		S[i]=(string)(s);
		len[i]=S[i].length();
	}
	m=read();
	while(m--){
		int x=read(),y=read();
		if(Ans[x][y]){
			printf("%d\n",Ans[x][y]);
			continue;
		}
		int Len=min(len[x],len[y]);
		for(int i=Len;i>=0;i--){
			bool flag=true;
			for(int j=0;j<i;j++){
				if(S[y][j]!=S[x][len[x]-i+j]){
					flag=false;break;
				}
			}
			if(flag){
				Ans[x][y]=i;
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}