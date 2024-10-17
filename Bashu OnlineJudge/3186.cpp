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
char str1[15],str2[1000005],str3[15];
int gtz,firstPosition,flag;
char *p=NULL;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
    scanf("%s",str1);
    getchar();
    gets(str2);
    p=str1;
    while(*p!='\0'){
		if(*p>='A'&&*p<='Z')*p=*p+32;
		p++;
	}
    p=str2;
    while(*p!='\0'){
		if(*p>='A'&&*p<='Z')*p=*p+32;
		p++;
	}
    i=j=flag=0;
    while(str2[i]!='\0'){
        if(str2[i]>='a'&&str2[i]<='z'){
            str3[j]=str2[i];
            i++;
            j++;
        }
        else{
            str3[j]='\0';
            if(strcmp(str1,str3)==0){
                gtz++;
                if(flag==0){
                    firstPosition=i-strlen(str1);
                    flag=1;
                } 
            }
            j=0;
            i++;
        }
    }
    if(flag==0) printf("-1\n");
    else printf("%d %d\n",gtz,firstPosition);
	return 0;
}