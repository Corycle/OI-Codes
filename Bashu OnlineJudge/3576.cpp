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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int n,b[1000005],s[5]={0,2,3,5,7};
long long a[1000005];//小根堆 
void up(){
	int i,j,k;
	k=a[0];
	while(k>1&&a[k]<a[k/2]){//若比父亲小，就上移 
		swap(a[k],a[k/2]);
		swap(b[k],b[k/2]);
		k=k/2;
	}
}
void down(){
	int i,j,k;
	i=1;
	while(i*2<=a[0]){
		if(i*2==a[0]||a[i*2]<a[i*2+1])j=i*2;//找当前i结点的最小孩子 
		else j=2*i+1;
		if(a[i]>a[j]){//若i结点比最小孩子值大就交换 
			swap(a[i],a[j]);
			swap(b[i],b[j]);
			i=j;//i结点变为当前最小孩子的位置 
		}
		else break;//否则已经排序完毕 
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	scanf("%d",&n);
	a[1]=1;a[0]=1;b[1]=2;
	for(int ti=1;ti<n;ti++){
		long long x[5]={0,a[1]*2,a[1]*3,a[1]*5,a[1]*7};
		
		for(i=1;i<=4;i++){
			if(b[1]<=s[i]){
				a[0]++;
				a[a[0]]=x[i];
				b[a[0]]=s[i];
				up();
			}
		}
//		cout<<ti<<" "<<a[1]<<" "<<b[1]<<endl;
		a[1]=a[a[0]];
		b[1]=b[a[0]];
		a[0]--;
		down();
	}
	printf("%lld",a[1]);
	return 0;
}