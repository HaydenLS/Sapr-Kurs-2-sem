#include <sstream>
#include"Methods.h"

using namespace std;
int main()
{
	setlocale(0, "Rus");

	ifstream file("Input.txt");
	ifstream request("Request.txt"); request.unsetf(ios::skipws);
	ofstream ofile("Output.txt");
	
	ofstream log("Log.txt");
	

	ListV list;

	Inf(list, file, ofile);
	
	log << "��������� ��������: \n";
	OutPut(list, log);
	log.close();
	cout << "���� ������� ������.\n\n";
	cout << "���������� ������: \n";
	list.OutList(cout);

	RequestHandler(list);
	log.close();
	file.close(); request.close(); ofile.close();
}