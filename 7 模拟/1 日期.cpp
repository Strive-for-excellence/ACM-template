1 计算日期差

#include <stdio.h>
#include <stdlib.h>
 
bool isLeapYear(int year)
{
	return ((year%4==0 && year%100!=0) || year%400==0);
}
// 以公元 1 年 1 月 1 日为基准，计算经过的日期 
int getDays(int year, int month, int day)
{
	int m[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(isLeapYear(year))
		m[2]++;
	int result = 0;
	for(int i = 1;i < year;i++)
	{
		result += 365;
		if(isLeapYear(i))
			result ++;
	}
	for(int i = 1;i < month;i++)
	{
		result += m[i];
	}
	result += day;
	
	return result;
}
int dayDis (int year1, int month1, int day1,
			int year2, int month2, int day2)
{
	return abs(getDays(year2, month2, day2) - getDays(year1, month1, day1));
}
	
int main(void)
{
	printf("%d\n",dayDis(2012, 9, 1, 2018, 3, 25));
	
	return 0;
} 
2 计算某一天星期几
int cal1(int y,int m,int d)
{
    if(m==1||m==2)
        m+=12,y--;
    int w=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
    return ++w;
}
int cal2(int y,int m,int d)
{
    if(m==1||m==2)
        m+=12,y--;
    int c=y/100,ty=y%100;
    int w=ty+ty/4+c/4-2*c+26*(m+1)/10+d-1;
    return w%7==0?7:(w+7)%7;
}
3 计算从2000 01 01 到9999 12 31 之间任意日期之间日期表示有多少个9
#include<bits/stdc++.h>

using namespace std;


int year,month,day;
int a1,b1,c1,a2,b2,c2;

const int maxn = 1e4+100;
int a[maxn];
int c[maxn]; // 代表当前年所有的9
// int mon[30] = {0,2,2,2,}
int run(int y){
    return y%400 == 0||(y%4==0&&y%100!=0);
}
int wanyue(int t,int y){
    if(t == 2) return 2+run(y);
    if(t == 9) return 3+30;
    return 3;
}
int wanyear(int t){
    int num = 0;
    int tt = t;
    while(tt > 0){
        if(tt % 10 == 9) num++;
        tt /= 10;
    }
    a[t] = num;
    int tmp = run(t);
    return num*(365+tmp)+65+tmp;
}
int mo[20] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int Howmuchday(int y,int t){
    if(t==2){
        return run(y)+28;
    }
    return mo[t];
}
int subday(int a,int b){
    int sum = 0;
    for(int i = a;i <= b; ++i)
        if(i%10 == 9)
            sum++;
    return sum;
}
int numsubday(int a,int b){
    return b-a+1;
}

int numsubday(int y,int b1,int c1,int b2,int c2){
    int num = 0;
    if(b1 == b2)
        return numsubday(c1,c2);
    for(int i = b1+1;i < b2; ++i)
        num += mo[i]+(i==2&&run(y));
    num += numsubday(c1,Howmuchday(y,b1));
    num += numsubday(1,c2);
    return num;
}
int FF(int t){
    int num = 0;
    int tt = t;
    while(tt > 0){
        if(tt % 10 == 9) num++;
        tt /= 10;
    }
    return num;
}
int submonth(int y,int b1,int c1,int b2,int c2){
    if(b1 == b2)
         return subday(c1,c2)+(c2-c1+1)*FF(b1);
    int sum = 0;
    for(int i = b1+1;i < b2; ++i)
        sum += wanyue(i,y);

    sum += subday(c1,Howmuchday(y,b1))+FF(b1)*(Howmuchday(y,b1)-c1+1);
    // cout<<sum<<endl;
    sum += subday(1,c2)+FF(b2)*(c2);
    return sum;
}

int subyear(int a1,int b1,int c1,int a2,int b2,int c2){
    if(a1 == a2)
        return numsubday(a1,b1,c1,b2,c2)*a[a1] + submonth(a1,b1,c1,b2,c2);
    int ans = 0;
    ans += c[a2-1]-c[a1];
    ans += numsubday(a1,b1,c1,12,31)*a[a1];
    ans += numsubday(a2,1,1,b2,c2)*a[a2];
    return ans + submonth(a1,b1,c1,12,31)+submonth(a2,1,1,b2,c2);
}

int main(void){

    for(int i = 2000;i < maxn; ++i){
        c[i] = wanyear(i);
        c[i] += c[i-1];
    }
    int T;
    cin>>T;
    while(T--){
        scanf("%d%d%d %d%d%d",&a1,&b1,&c1,&a2,&b2,&c2);
        int ans = subyear(a1,b1,c1,a2,b2,c2);
        printf("%d\n",ans);
    }
    return 0;
}
