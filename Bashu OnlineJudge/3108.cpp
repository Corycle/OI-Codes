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
#define inf 0x3f3f3f3f
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
int n,m,p[1005],minn;
long long get1(long long minite){//统计minite分钟内能容纳小朋友的总人数  
	int i,j,k;
	long long number=0;
	for(i=0;i<m&&number<n;i++){
		number+=(minite+p[i]-1)/p[i];
	}
	return number;
}
long long Find1(){ //找到n这个人玩飞机的时间 
	long long l=0,r=((long long)minn)*n,mid,num;
	while(l<r){
		mid=l+r>>1;
		num=get1(mid);
		if(num>=n)r=mid;
		else l=mid+1;
	}
	return r;
}
int Find2(long long minite){ //寻找所玩飞机的编号 
	int i,j,k;
	long long n1=n-get1(minite-1);//得出最后一分钟内有多少个小朋友正在玩飞机
	minite--;
	for(i=0;i<m;i++){
		if(minite%p[i] == 0){//如果求余为0，那么一定会有小朋友上飞机
			n1--;
			if(!n1)return i+1;
		}
	}
	return -1;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	minn=inf;
	for(i=0;i<m;i++){
		p[i]=read();
		minn=min(minn,p[i]);
	}
	long long time=Find1();//先二分找出n这个人玩飞机的时间
	int id=Find2(time);//根据这个时间找出n小朋友玩的飞机
	printf("%d",id);
	return 0;
}