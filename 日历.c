#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void test();
void calendar(int year, int n);
int Is_Correct_input(int year, int n);
void Pmonth(int* count);
void Pweek();
void date(int year, int n, int* month, int* Mon, int* mon, int* mo , int* m , int* z);
void Pspace(int n);
int Get_first_day_week(int year, int** month);
void Print_date1(int n);
void Print_date2(int n, int max);
void Print_date3(int n, int max);
void Print_date4(int n, int max);
void Print_date5(int n, int max);
void Print_date6(int n, int max);
int Is_leap_year(int year);
int Total_leap_year(int year);
int Max_day_month(int year, int month);
int NumDayYear(int year, int month, int day);
int DayWeek(int year, int month, int day);

int main()
{
	test();
	return 0;
}

void test()
{
	int year = -1;
	int n = 0;
	printf("年  份: ");
	scanf("%d", &year);
	printf("分栏数: ");
	scanf("%d", &n);
	if (Is_Correct_input(year, n))
	{
		calendar(year, n);
	}
	else
	{
		exit(1);
	}
}

int Is_Correct_input(int year, int n)
{
	return n > 0 && year != 0;
}

void calendar(int year, int n)
{
	//打印表头
	printf("%41d年年历\n", year);
	putchar('\n');
	//打印月份
	int count = 1;
	//定义函数打印表头的月份
	// 定义循环使用的变量
	int i = 0, j = 0, k = 0; 
	//定义变量计数
	int x = 0;
	int y = 0;
	//定义循环跳出条件
	int ok = 1;
	//传递月份
	int month = 1;
	int Mon = 1;
	int mon = 1;
	int m = 1;
	int mo = 1;
	int z = 1;
	for (i = 0; ok ; i++)
	{
		for (j = 0; ok && j < n; j++)
		{
			x++;
			//打印月份
			Pmonth(&count);
			if (x == 12)
			{
				ok = 0;
			}
		}
		putchar('\n');
			ok = 1;
		for (j = 0; ok && j < n; j++)
		{
			//打印周
			Pweek();
			y++;
			if (y == 12)
			{
				ok = 0;
			}
		}
		putchar('\n');
			//ok = 1;
		/*for (j = 0; ok && j < n; j++)
		{
			//打印天
			date(year,n, month);
			month++;
			z++;
			if (z == 12)
			{
				ok = 0;
			}
		}*/
		date(year, n, &month ,&Mon, &mon ,&mo ,&m ,&z);
		putchar('\n');
	}
	
}

void Pmonth(int* count)
{
	printf("%11d月          ", *count);
	(*count)++;
}

void Pweek()
{
	printf(" 日 一 二 三 四 五 六 ");
}

void date(int year,int n,int* month , int* Mon , int* mon , int* mo ,int *m ,int* z)
{
	//计算每月第一天是周几
	int first_day_week = 0;
	//int month = 1;
	//打印天
	int i = 0 , j = 0;
	int a[12] = { 0 };
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &month);
		//打印空格
		Pspace(first_day_week);
		Print_date1(first_day_week);
	}
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &Mon);
		Print_date2(first_day_week , Max_day_month (year ,*Mon - 1));
	}
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &mon);
		Print_date3(first_day_week, Max_day_month(year, *mon - 1));
	}
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &mo);
		Print_date4(first_day_week, Max_day_month(year, *mo - 1));
	}
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &m);
		Print_date5(first_day_week, Max_day_month(year, *m - 1));
	}
	putchar('\n');
	for (i = 0; i < n; i++)
	{
		first_day_week = Get_first_day_week(year, &z);
		Print_date6(first_day_week, Max_day_month(year, *z - 1));
	}
	putchar('\n');
}
	//打印第一行每一天
void Print_date1(int n )
{
	int i = 0;
	int j = 0;
	n = 7 - n;
	putchar(' ');
	//第一行
	for (i = 1; i <= n ; i++)
	{
		printf(" %d ", i);
	}
}

void Print_date2(int n, int max)
{
	int i = 0;
	int count = 0;
	for (i = 7 - n + 1; count != 7 && i <= max ; i++)
	{
		printf(" %2d", i);
		count++;
	}
	putchar(' ');

}
void Print_date3(int n, int max)
{
	int i = 0;
	int count = 0;
	for (i = 14 - n + 1; count != 7 && i <= max; i++)
	{
		printf(" %2d", i);
		count++;
	}
	putchar(' ');
}
void Print_date4(int n, int max)
{
	int i = 0;
	int count = 0;
	for (i = 21 - n + 1; count != 7 && i <= max; i++)
	{
		printf(" %2d", i);
		count++;
	}
	putchar(' ');
}
void Print_date5(int n, int max)
{
	int i = 0;
	int count = 0;
	for (i = 28 - n + 1; count != 7 && i <= max; i++)
	{
		printf(" %2d", i);
		count++;
	}
	putchar(' ');
	//如果某个月份打印完成
	//就打印若干空格
	int m = 7 - n + 28;
	if (i > max)
		for (i = max ; i < m; i++)
		{
			printf("   ");
		}
}
void Print_date6(int n, int max)
{
	int i = 0;
	int count = 0;
	for (i = 35 - n + 1; count != 7 && i <= max; i++)
	{
		printf(" %2d", i);
		count++;
	}
	putchar(' ');
	//如果某个月份打印完成
	//就打印若干空格
	int m = 42 - n + 1;
	if (i > max)
		for (; i < m; i++)
		{
			printf("   ");
		}
}
	//打印空格
void Pspace(int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("   ");
	}
}
	//判断是否是闰年
int Is_leap_year (int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}
	//计算闰年总数
int Total_leap_year(int year)
{
	return year / 4 - year / 100 + year / 400;
}
	// 计算一个月最大的天数
int Max_day_month(int year, int month)
{
	int a = 0;
	if (year > 0)
	{
		switch (month)
		{
		case 1: a = 31; break;
		case 2: a = 28 + Is_leap_year(year); break;
		case 3: a = 31; break;
		case 4: a = 30; break;
		case 5: a = 31; break;
		case 6: a = 30; break;
		case 7: a = 31; break;
		case 8: a = 31; break;
		case 9: a = 30; break;
		case 10:a = 31; break;
		case 11:a = 30; break;
		case 12:a = 31; break;
		default:a = 0;
		}
	}
	return a;
}
	//计算概念天数
int NumDayYear(int year, int month, int day)
{
	int n = 0;
	if (year > 0)
	{
		switch (month)
		{
		case 1: n = day; break;
		case 2: n = day + 31; break;
		case 3: n = 59 + day + Is_leap_year(year); break;
		case 4: n = 90 + day + Is_leap_year(year); break;
		case 5: n = 120 + day + Is_leap_year(year); break;
		case 6: n = 151 + day + Is_leap_year(year); break;
		case 7: n = 181 + day + Is_leap_year(year); break;
		case 8: n = 212 + day + Is_leap_year(year); break;
		case 9: n = 243 + day + Is_leap_year(year); break;
		case 10:n = 273 + day + Is_leap_year(year); break;
		case 11:n = 304 + day + Is_leap_year(year); break;
		case 12:n = 334 + day + Is_leap_year(year); break;
		}
	}
	return n;
}
	//求总天数
int TotalDay(int year, int month, int day)
{
	int a = 0;
	if (year > 0)
		if (month >= 1 && month <= 12)
			if (day > 0 && day <= Max_day_month(year, month))
				a = (year - 1) * 365 + Total_leap_year(year) + NumDayYear(year, month, day) - Is_leap_year(year);
	return a;
}
	//计算星期
int DayWeek(int year, int month, int day)
{
	int week = -1;
	int a = 0;
	if (TotalDay(year, month, day))
	{
		a = TotalDay(year, month, day);
		a %= 7;
		week = a;
	}
	return week;
}

int Get_first_day_week(int year, int** month)
{
	//介于1年1月1日为周一
	//通过计算天数来判断
	//计算该年第一天到公元1年第一天总天数
	int total = TotalDay(year, **month, 1);
	int week = DayWeek(year, **month, 1);
	(**month)++;
	return week;
}