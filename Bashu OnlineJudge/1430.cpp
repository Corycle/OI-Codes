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
int n,m,tot,ans;
char words[15],sentences[1000005];
bool flag[1000005],f[505];
struct tree{
	int next[30];
}t[505];
void build(){
	int i,j,k;
	int len=strlen(words)-1,now=0;
	for(i=0;i<=len;i++){
		int x=words[i]-'a'+1;
//		cout<<x<<endl;
		if(t[now].next[x]==0)t[now].next[x]=++tot;
		now=t[now].next[x];
	}
	f[now]=1;
}
void find(){
	int i,j,k;
	memset(flag,0,sizeof(flag));
	ans=0;
	flag[0]=1;
	int len=strlen(sentences+1),now;
//	cout<<len<<endl;
	for(i=0;i<=len;i++){
//		cout<<flag[i];
		if(flag[i])ans=i;
		else continue;
		now=0;
		for(j=i+1;j<=len;j++){
			int x=sentences[j]-'a'+1;
//			cout<<sentences[j];
//			cout<<now<<" "<<x<<" "<<t[now].next[x]<<endl;
			now=t[now].next[x];
			if(now==0)break;
			if(f[now])flag[j]=1;
        }
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		scanf("%s",&words);
		build();
	}
//	cout<<t[7].next[8]<<endl;
	for(i=1;i<=m;i++){
		scanf("%s",sentences+1);
		find();
		printf("%d\n",ans);
	}
	return 0;
}