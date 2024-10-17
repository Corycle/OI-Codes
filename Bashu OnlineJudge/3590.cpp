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
char str[30],s1[30],s2[30];
int tot;
struct tree{
	int next[27];
	char a[30];
}t[1000005];
void build(char a[],char b[]){
	int i,j,k;
	int now=0,len=strlen(a)-1;
	for(i=0;i<=len;i++){
		int x=a[i]-'a'+1;
		if(!t[now].next[x])t[now].next[x]=++tot;
		now=t[now].next[x];
	}
	memcpy(t[now].a,b,sizeof(t[now].a));
}
void Find(char a[]){
	int i,j,k;
	int now=0,len=strlen(a)-1;
	for(i=0;i<=len;i++){
		int x=a[i]-'a'+1;
		if(!t[now].next[x]){
			printf("eh\n");
			return;
		}
		now=t[now].next[x];
	}
	if(strlen(t[now].a))printf("%s\n",t[now].a);
	else printf("eh\n");
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	while(1){
		cin.getline(str,30);
		if(strlen(str)==0)break;
		int l1=-1,l2=-1,flag=1;
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		for(i=0;i<=25;i++){
			if(str[i]==' '){
				flag=2;
				continue;
			}
			if(flag==1)s1[++l1]=str[i];
			if(flag==2)s2[++l2]=str[i];
		}
//		cout<<s1<<" "<<s2<<endl;
		build(s2,s1);
	}
//	cout<<tot<<endl;
//	cout<<t[5].a<<endl;
	while(scanf("%s",s1)!=EOF){
		Find(s1);
	}
	return 0;
}