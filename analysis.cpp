#include "analysis.h"

#include <iostream>

#include <sstream>
#include <string>
#include <regex>

#include <cmath>
#include <windows.h>
#include <vector>

using namespace std;

#define PI 3.141592653589793238462643

struct angle
{
	double d;
	double m;
	double s;
}; //angle

vector<angle> angles;

struct angle sum_an()
{

	int i;
	struct angle sum = {0, 0, 0};
	input_an();
	for (i = 0; i < angles.size(); i++)
	{
		sum.d = angles[i].d + sum.d;
		sum.m = angles[i].m + sum.m;
		sum.s = angles[i].s + sum.s;
	}

	cal(sum);

	//printf("\n\t\t总计为%g°%g′%g″.",sum.d,sum.m,sum.s);
	return sum;
}

void input_n(vector<double> &arr)
{
	int i;
	double d;

	string str;

	fflush(stdin);
	cout << "\n\t\t输入一行数值，任意分割符（比如空一格）：\n\t\t";

	getline(cin, str);
	stringstream s(str);
	for (;;)
	{
		if (!(s >> d))
		{
			break;
		}
		arr.push_back(d);
	}

	//单独回车符必须等待输入数值
	/*
	for(i=0;i<n;i++)
	printf("%.2f ",d=*(arr+i));
	*/

	return;
}

double sum(vector<double> &d)
{
	int i;
	double sum = 0;
	//printf("\n\t\t请输入一串数据用以计算和，回车键取消：");
	input_n(d);
	for (double i : d)
		sum = i + sum;
	//printf("\n\t\t总和为%g",sum);
	return sum;
	//piece program until it end with zero
}

void input_an()
{
	string str;

	cout << "\n\t\t请输入一组数据,以任何方式分隔度 分 秒(如30.89 54.76 51.5(30.89度54.76分51.5秒))，回车切换输入下一个角度\n\t\t，非数字字符结束：\n\t\t";
	fflush(stdin);
	while (getline(cin, str))
	{
		cout << "\n\t\t";
		stringstream s(str);

		angle a = {0, 0, 0};

		if (!(s >> a.d))
		{
			cout << "\n\t\t输入角度为：";
			break;
		}
		s >> a.m;
		s >> a.s;

		angles.push_back(a);
	}
	//单独回车符必须等待输入数值
	for (angle a : angles)
	{
		printf("\t\t%g°%g′%g″", a.d, a.m, a.s);
	}
}

void cal(struct angle &sum)
{
	int temp;
	temp = sum.s / 60.0; //进位
	sum.s = (float)fmod(sum.s, 60.0);
	sum.m = sum.m + temp;
	temp = sum.m / 60.0; //进位
	sum.m = (float)fmod(sum.m, 60.0);
	sum.d = sum.d + temp;
}

void cal_rad(struct angle &sum)
{
	sum.s = sum.s / 60.0;
	sum.m = (sum.m + sum.s) / 60.0;
	sum.d = (sum.d + sum.m / 60.0) * PI / 180.0;
	//printf("\n\t\t转换后结果为 %g",sum->d);
}

void scan_yn(struct angle &an)
{
	cout << "\t\t以任何方式分割度 分 秒(如30.89 54.76 51.5(30.89度54.76分51.5秒)):		\n\t\t";
	/*char o;
		do{	
		scanf("%c",&o); 
		}while(o!='+'&&o!='-');
		switch(o){
		case '+':*/
	fflush(stdin);
	string str;

	for (;;)
	{
		getline(cin, str);
		stringstream s(str);
		if (!(s >> an.d))
		{
			cout << "非合法数字！";
			continue;
		}
		s >> an.m;
		s >> an.s;
		break;
	}

	cout << "\n\t\t输入角度为：";
	printf("\t\t%g°%g′%g″", an.d, an.m, an.s);

	/*break;
		case '-':
			int d,m,s;
			scanf("%d.%d.%d",&d,&m,&s);
			a->d=-d;a->m=-m;a->s=-s;
		break;
		default: 
		
		break;
		
		}*/
	//getchar();
}

void icor_angle()
{
	struct angle icor, ib, ie = {0, 0, 0};

	int m;

	printf("\n\t\t请输入观测全部值（请严格按照要求输入！！！)");
	icor = sum_an();

	printf("\n\n\t\t请输入起始值: \n");
	scan_yn(ib);
	printf("\n\t\t请输入测点数：\n\t\t");
	cin >> m;
	printf("\n\t\t请输入结束值: \n");
	scan_yn(ie);
	icor.d = icor.d + ib.d - (m - 2) * 180.0 - ie.d;
	icor.m = icor.m + ib.m - ie.m;
	icor.s = icor.s + ib.s - ie.s;
	cal(icor);
	cout << "\n\t\t改正数改正角为：" << icor.d << "°" << icor.m << "′" << icor.s << "″";
}

void grid_bearing()
{
	struct angle alpha_a1, alpha_ba, beta_agai = {0, 0, 0};

	printf("\n\t\t计算模式为αa1=αba-180+βa改");
	printf("\n\t\t请输入α_BA角：	\n");
	scan_yn(alpha_ba);
	printf("\n\t\t请输入β_A改:		\n");
	scan_yn(beta_agai);
	printf("\n\t\t所得的坐标方位角为%g°%g′%g″\n", alpha_ba.d - 180 + beta_agai.d, (float)(alpha_ba.m + beta_agai.m), (float)(alpha_ba.s + beta_agai.s));
}

void incre()
{
	struct angle alpha_a1 = {0, 0, 0};
	double D_a1;
	printf("\n\t\t计算模式为ΔX_a1=D_a1*cos αa1,ΔY_a1=D_a1*sin αa1");
	printf("\n\t\t请输入α_a1角：	\n");
	scan_yn(alpha_a1);

	cal_rad(alpha_a1);

	printf("\n\t\t请输入D_a1的长度：	\n\t\t");
	cin >> D_a1;
	//printf("\n\t\t%g",D_a1);

	printf("\n\t\t增量计算的结果为ΔX_a1= %g,ΔY_a1= %g\n", D_a1 * cos(alpha_a1.d), D_a1 * sin(alpha_a1.d));
}

void cor()
{
	double x_e, x_b, y_e, y_b;
	double d_1;
	vector<double> x_all, y_all, d_all;

	double cor_x, cor_y;

	double x, y, d;

	double x_o, y_o;

	printf("\n\t\t计算模式为ΣΔX(Y)测-(X(Y)结束-X(Y)起始)=Fx(y)");
	printf("\n\t\t请输入ΣΔX中的ΔX全部值：	");

	x = sum(x_all);
	printf("\n\t\t请输入ΣΔY中的ΔY全部值：	");
	y = sum(y_all);

	printf("\n\t\t请输入X起始:		");
	cin >> x_b;
	printf("\n\t\t请输入X结束:		");
	cin >> x_e;

	printf("\n\t\t请输入Y起始:		");
	cin >> y_b;
	printf("\n\t\t请输入Y结束:		");
	cin >> y_e;

	printf("\n\t\t请输入D的全部值:		");
	d = sum(d_all);
	printf("\n\t\t请输入D1的值：	");
	cin >> d_1;

	cor_x = (-(x - (x_e - x_b))) / d * d_1;
	cor_y = (-(y - (y_e - y_b))) / d * d_1;
	cout << "\n\t\tx和y的改正系数分别为 " << cor_x << "和" << cor_y;

	cout << "\n\t\t请输入ΔX原:	";
	cin >> x_o;
	cout << "\n\t\t请输入ΔY原：	";
	cin >> y_o;

	cout << "\n\t\tΔX改= " << cor_x + x_o << ",ΔY改= " << cor_y + y_o << " \n";
}

void x_y()
{
	vector<double> x;
	vector<double> y;
	double delta_x;
	double delta_y;

	cout << "\n\t\t请输入x坐标的所有值：	(x和y的值一一对应)\n\t\t";
	input_n(x);

	cout << "\n\t\t请输入ΔX改的值：	";
	cin >> delta_x;

	cout << "\n\t\t请输入y坐标的所有值：	(y和x的值一一对应，缺省则为0)\n\t\t";
	input_n(y);
	cout << "\n\t\t请输入ΔY改的值:	";
	cin >> delta_y;

	for (int i = 0; i < x.size(); i++)
		cout << "\n\t\t坐标修正为(" << x[i] + delta_x << "," << y[i] + delta_y << ")\n";
}
