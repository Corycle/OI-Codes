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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct node{
	int type,id,data;
}a[100005],tmp[100005];
int ans[50005];
bool cmp(node x,node y){
	return x.id==y.id?x.type<y.type:x.id<y.id;
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	int p=l,q=mid+1;
	int num=l,sum=0;
	while(p<=mid&&q<=r){
		if(cmp(a[p],a[q])){
			if(a[p].type==1)sum+=a[p].data;
			tmp[num++]=a[p++];
		}
		else{
			if(a[q].type==2)ans[a[q].data]-=sum;
			if(a[q].type==3)ans[a[q].data]+=sum;
			tmp[num++]=a[q++];
		}
	}
	while(p<=mid){
		tmp[num++]=a[p++];
	}
	while(q<=r){
		if(a[q].type==2)ans[a[q].data]-=sum;
		if(a[q].type==3)ans[a[q].data]+=sum;
		tmp[num++]=a[q++];
	}
	for(int i=l;i<=r;i++)a[i]=tmp[i];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int n=read(),m=read();
	int cnt=0,qnt=0;
	for(int i=1;i<=m;i++){
		char s[5];
		scanf("%s",s);
		int x=read(),y=read();
		if(s[1]=='d')a[++cnt]=(node){1,x,y};//Add
		if(s[1]=='u')a[++cnt]=(node){1,x,-y};//Sub
		if(s[1]=='s'){//Ask
			qnt++;
			a[++cnt]=(node){2,x-1,qnt};
			a[++cnt]=(node){3,y,qnt};
		}
	}
	CDQ(1,cnt);
	for(int i=1;i<=qnt;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
