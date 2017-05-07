// generalList.cpp : 定义控制台应用程序的入口点。
//
#include"iostream"
using namespace std;
#include"generalList.h"
void testGeneralList()
{
	GeneralList g1("((()))");
	GeneralList g2("(a,b)");
	GeneralList g3("(a,b,(c,d))");
	GeneralList g4("(a,b,(c,d),(e,(f),g))");
	g1.Display();
	g2.Display();
	g3.Display();
	g4.Display();
	cout << g1.Size() << endl;  //0  
	cout << g2.Size() << endl;  //2  
	cout << g3.Size() << endl;  //4  
	cout << g4.Size() << endl;  //7  
	cout << g1.Depth() << endl; //3  
	cout << g2.Depth() << endl; //1  
	cout << g3.Depth() << endl; //2  
	cout << g4.Depth() << endl; //3  
	GeneralList g5(g4);
	g5.Display();

	GeneralList g6;
	g6 = g5;
	g6.Display();
}
int main()
{
	testGeneralList();
	system("pause");
	return 0;
}