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
int fun(int x,int y)//x,y的最大公约数
{  
	if(y==0) return x;  
	else return fun(y,x%y);  
}  
int main()
{  
	int k; 
	int a,b,l;//输出 
	int a1,b1;//答案 
	int i,j;//i和j做循环之用  
	double s1,s2,s3;  
	scanf("%d%d%d",&a,&b,&l);  
	s1=a*1.0/b;//变为double的数  
	s3=l*1.0;//变为double的数   
	for(i=1;i<=l;i++)//枚举l次  
		for(j=1;j<=l;j++)  
			if(fun(i,j)==1)//如果最大公约数是1，执行也 
			{  
				s2=i*1.0/j;//变为int类型的，继续执行  
				if(s2>=s1&&s2-s1<s3)//A’/B’≥ A/B且A’/B’- A/B的值尽可能小。
				{  
					a1=i;
					b1=j;  
					s3=s2-s1;  
				}  
			}  
	printf("%d %d\n",a1,b1);  
	return 0;  
}  