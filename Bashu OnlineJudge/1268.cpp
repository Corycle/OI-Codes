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
//stack<_>_;
//queue<int>q;
//priority_queue<_>f;
//priority_queue<_,vector<int>,greater<int> >f;
double ans,d1,d2,c,lcx,p[105],d[105];
int n,gtz; 
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k,yuan;
	cin>>d1>>c>>d2>>p[0]>>n;
    for(i=1;i<=n;i++){
    	cin>>j;
    	cin>>d[i]>>p[i];
	}
    n++;
    d[n]=d1;
    while(1){
        k=-1;
        for(i=gtz+1;i<=n;i++){
            if(d[i]-d[gtz]<=c*d2){
                if(p[i]<p[gtz]){
                    k=i;
                    break;
                }
            }
            else{
                yuan=i-1;
                break;
            }
        }
        if(k<0){
            if(yuan==gtz){
                printf("No solution");
                return 0;
            }
            ans+=p[gtz]*(c-lcx);
            lcx=c-(d[yuan]-d[gtz])/d2;
            gtz=yuan;
        }
        else{
            if(lcx*d2>=d[k]-d[gtz])
                lcx-=(d[k]-d[gtz])/d2;
            else{
                ans+=p[gtz]*((d[k]-d[gtz])/d2-lcx);
                lcx=0;
            }
            gtz=k;
        }
        if(gtz==n)break;
    }
    cout<<fixed<<setprecision(2)<<ans;
	return 0;
}