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
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int lxs,rxs,lcs,rcs,lor,num,opera;  
int main(){
	char c,x;
    while(scanf("%c",&c)!=EOF){
        if(c>='0'&&c<='9')num=num*10+c-'0';
		else if(c=='+'){
            if(lor==0){
                if(opera==0)lcs+=num;
				else lcs-=num;
            }
			else{
                if(opera==0)rcs+=num;
				else rcs-=num;
            }
            num=opera=0;                
        }
		else if(c=='-'){
            if(lor==0){
                if(opera==0)lcs+=num;
				else lcs-=num;
            }
			else{
                if(opera==0)rcs+=num;
                else rcs-=num;
            }
            num=0;
            opera=1;
        }
		else if(c=='='){
            if(lor==0){             
                if(opera==0)lcs+=num;
                else lcs-=num;
            }
			else{
                if(opera==0)rcs+=num;
                else rcs-=num;
            }
            num=opera=0;
            lor=1;
        }
		else if(c>='a'&&c<='z'){
            x=c;
            if(num==0)num=1;
            if(lor==0){
                if(opera==0)lxs+=num;
                else lxs-=num;
            }
			else{
                if(opera==0)rxs+=num;
                else rxs-=num;
            }
            num=0;
        }
    }
    if(num!=0){  
        if(opera==0)rcs+=num;
        else rcs-=num;
    }
    double ans=(double)(rcs-lcs)/(double)(lxs-rxs);
    if(ans==0.0){
        ans=abs(ans);
    }
    printf("%c=%.3f",x,ans);
	return 0;
}