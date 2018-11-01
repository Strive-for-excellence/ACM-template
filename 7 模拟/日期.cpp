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
