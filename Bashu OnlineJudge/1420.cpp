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
char key[405],words[105][105];
int n,tot,ans[405],len;
struct tree{
	int next[27],flag;
}t[10005];
void Build(int num){
	int i,j,k;
	int now=0;
	k=strlen(words[num])-1;
	for(i=0;i<=k;i++){
		int x=words[num][i]-'a'+1;
		if(t[now].next[x])now=t[now].next[x];
		else{
			t[now].next[x]=++tot;
			now=tot;
		}
	}
	t[now].flag=1;
//	cout<<now<<endl;
}
void Find(int s,int cnt){
	int i,j,k;
	int now=0;
//	cout<<s<<" "<<cnt<<endl;
	for(i=s;i<=len;i++){
		int x=key[i]-'a'+1;
		if(t[now].next[x])now=t[now].next[x];
		else return;
		if(t[now].flag&&ans[i]>cnt){
//			cout<<s<<" "<<cnt<<" "<<now<<" "<<t[now].flag<<endl;
			ans[i]=cnt;
			Find(i+1,cnt+1);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	memset(ans,0x3f,sizeof(ans));
	scanf("%s",&key);
	len=strlen(key)-1;
	n=read();
	for(i=1;i<=n;i++){
		scanf("%s",&words[i]);
		Build(i);
	}
//	cout<<tot<<" "<<t[15].next[18]<<endl;
	Find(0,1);
//	for(i=0;i<=len;i++)printf("%d\n",ans[i]);
	printf("%d",ans[len]);
	return 0;
}