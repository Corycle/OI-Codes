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
int n,f[500005],s;
struct dzh1{
	int x,y;
}dzh[500005];
bool cmp(dzh1 x,dzh1 y){
	return x.x<y.x;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>dzh[i].x>>dzh[i].y;
		f[i]=1;
	}
	sort(dzh+1,dzh+n+1,cmp);
//	for(i=1;i<=n;i++){
//		for(j=1;j<=i;j++){
//			if(dzh[i].y>dzh[j].y){
//				if(f[j]+1>f[i])f[i]=f[j]+1;
//				p=max(p,max(f[i],f[j]));
//			}
//		}
//	}
	int l,h,mid,p=0;
	for(i=1;i<=n;i++){
        if(dzh[i].y>f[p]){  
            f[++p]=dzh[i].y;  
        }
        else{  
            l=1,h=p;
            while(l<=h){  
                mid=(l+h)/2;  
                if(dzh[i].y>f[mid])l=mid+1;
                else h=mid-1;
            } 
            f[l]=dzh[i].y;
        }  
    }
	cout<<p;
	return 0;
}