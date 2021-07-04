#include <cmath>
#include <iostream>
#include "analysis.cpp"

using namespace std;

void disp()
{
	int i;
	SetConsoleTitle("Unity综合地理信息计算软件(ver. 1.3)");
	printf("\n\t\t请选择你所要的应用界面:(按1标识魅彩金，按2标识极客绿):\n\t\t");
	cin >> i;
	if (i == 1)
		system("color 06");
	if (i == 2)
		system("color 02");
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main()
{
	//printf("%d",fac(5));

	//printf("\n总计为%d",sum(input()));
	//return 0;
	system("chcp 65001");
	disp();
	cout << "\t\t";

	int io;
	for (;;)
	{
		cout << "\n\n\t\t请选择要实现的功能(用数字选择)：\n";
		cout << "\t\t改正数改正角(按1): \n";
		cout << "\t\t坐标方位角(按2): \n";
		cout << "\t\t增量计算(按3): \n";
		cout << "\t\t改正系数计算(按4): \n";
		cout << "\t\t坐标值(按5): \n";
		cout << "\t\t修改控制行颜色(按0): \n\t\t";
		//cout << "\t\tExit(按0): \n";
		angles.empty();
		cin >> io;
		switch (io)
		{
		case 0:
			disp();
			break;
		case 1:
			icor_angle();
			break;
		case 2:
			grid_bearing();
			break;
		case 3:
			incre();
			break;
		case 4:
			cor();
			break;
		case 5:
			x_y();
			break;
		default:
			continue;
		}
	}
	return 0;
}
