#include <sstream>
#include"Methods.h"

using namespace std;
int main()
{
	setlocale(0, "Rus");

	ifstream file("Input.txt");
	ifstream request("Request.txt"); request.unsetf(ios::skipws);
	ofstream ofile("Output.txt");

	ListV list;

	Inf(list, file, ofile);
	OutPut(list, ofile);

	cout << "���� ������� ������.\n\n";
	cout << "���������� ������: \n";
	list.OutList(cout);


	RequestHandler(list);

	file.close(); request.close(); ofile.close();
}