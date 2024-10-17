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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,lst,tot=-1;
struct Tree{int len,sum,fail,ch[30];}t[N];
void Insert(int pos){
	int x=lst,num=s[pos]-'a'+1;
	while(s[pos-t[x].len-1]!=s[pos])x=t[x].fail;
	if(!t[x].ch[num]){
		int y=++tot,p=t[x].fail;t[y].len=t[x].len+2;
		while(s[pos-t[p].len-1]!=s[pos])p=t[p].fail;
		t[y].fail=t[p].ch[num];t[x].ch[num]=y;
	}
	t[t[x].ch[num]].sum++;
	lst=t[x].ch[num];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	t[++tot].len=0;t[tot].fail=1;
	t[++tot].len=-1;t[tot].fail=1;
	for(int i=1;i<=n;i++)Insert(i);
	for(int i=tot;i>=1;i--)t[t[i].fail].sum+=t[i].sum;
	for(int i=1;i<=tot;i++)Ans=max(Ans,1ll*t[i].len*t[i].sum);
	printf("%lld",Ans);
	return 0;
}