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
int n,num,x[105],y[105],last[105],t[105],sum[105];
char s[105],a[105];
map<char,int>p;
int get_num(){
	scanf("%s",s+1);
	int len=strlen(s+1);
	if(len==1&&s[1]=='n')return 105;
	int sum=0;
	for(int i=1;i<=len;i++)sum=sum*10+s[i]-'0';
	return sum;
}
void init(){
	n=num=0;
	p.clear();
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	memset(t,0,sizeof(t));
	memset(a,0,sizeof(a));
	memset(sum,0,sizeof(sum));
	memset(last,0,sizeof(last));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int T=read();
	while(T--){
		init();
		n=read();
		scanf("%s",s+1);
		num=0;//n^num
		int len=strlen(s+1);
		for(i=5;i<len;i++){
			if('0'<=s[i]&&s[i]<='9')num=num*10+s[i]-'0';
		}
		char ch;
		bool flag=false;
		int cnt=0;
		for(i=1;i<=n;i++){
			cin>>ch;//F||E
			if(ch=='F'){
				cin>>a[i];
				if(p[a[i]])flag=true;
				p[a[i]]=1;
				x[i]=get_num();
				y[i]=get_num();
				if(flag)continue;
				cnt++;
				sum[i]=cnt;
				last[cnt]=i;
			}
			else{
				x[i]=y[i]=0;
				if(flag)continue;
				t[last[cnt]]=i;
				t[i]=last[cnt];
				sum[i]=cnt;
				p[a[t[i]]]=0;
				cnt--;
				if(cnt<0)flag=true;
//				if(cnt<0)cout<<111111<<endl;
			}
		}
		if(cnt!=0)flag=true;
		if(flag){//ERR
			printf("ERR\n");
			continue;
		}
		int ans=0;
		cnt=0;
		for(i=1;i<=n;i++){
			int lcx=0;
			if(t[i]>i){
				if(x[i]>y[i])lcx=1;
				if(x[i]<y[i]&&y[i]==105)lcx=2;
				if(lcx==1)i=t[i];
				if(lcx==2)cnt++;
				ans=max(ans,cnt);
			}
			else{
				if(x[t[i]]<y[t[i]]&&y[t[i]]==105)lcx=2;
				if(lcx==2)cnt--;
			}
		}
//		cout<<ans<<" "<<num<<endl;
		if(ans==num)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}