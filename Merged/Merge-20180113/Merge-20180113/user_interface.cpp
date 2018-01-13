#include"Interface/Interface.h"
using namespace std;
#include<windows.h>


int main()
{	
	
	SetConsoleOutputCP(951);
	Interface a(72,0,72,0,0,0,0);
	a.gamemodeoption();

	system("pause");
	return 0;
}
