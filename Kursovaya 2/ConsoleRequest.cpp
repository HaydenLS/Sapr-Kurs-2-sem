#include "ConsoleRequest.h"

using namespace std;

// ���������� ������ � ������� �����.
void CreateArray(ListH& l1, ListH& l2, int* number1, int sizel1, int* number2, int sizel2)
{
	// ��� 1 ������.

	l1.cur = l1.head;
	int j = 0; // ���������� ��� ������� �� ������� int.
	while (l1.cur != nullptr)
	{
		for (int i = 0; i < l1.cur->elem.Len(); i++)
		{
			number1[j++] = l1.cur->elem[i] - '0';
		}
		l1.cur = l1.cur->strNext;
	}

	// ���� ��� ������� ������.
	// 
	// ��� 2 ������.

	l2.cur = l2.head;
	j = 0; // ���������� ��� ������� �� ������� int.
	while (l2.cur != nullptr)
	{
		for (int i = 0; i < l2.cur->elem.Len(); i++)
		{
			number2[j++] = l2.cur->elem[i] - '0';
		}
		l2.cur = l2.cur->strNext;
	}
}

// ������� �� Int ������
void MakeList(ListH& list, int* number, int size)
{
	// ������� �������� ������, ���� �� ��� ��������.
	list.~ListH();

	//int j = 0; // �������

	int listSize = size / N + (size % N != 0);

	String tempstr;

	int k = size; // ������� ��������� �������� ��������.
	int needToAdd = (k - N) >= 0 ? N : k % N; // ������� ��������� ����� �������� �� ������ ����.
	int all = 0;
	while (k > 0)
	{
		needToAdd = (k - N) >= 0 ? N : k % N;

		tempstr.SetLen(needToAdd);


		for (int i = 0; i < needToAdd; i++)
		{
			tempstr[i] = number[all++] + '0';
		}

		list.push_back(tempstr);
		tempstr.Clear();

		k -= needToAdd;
	}
}

// ���������� �������.
void DoRequest(ListV& list, ListH& request)
{
	OPEN_LOG

	

	char operation = request[0][0];

	int i1 = request[1].Znach() - 1, i2 = request[2].Znach() - 1; // ������� �����
	
	

	if (i1 >= list.size || i2 >= list.size)
	{
		cout << RED << "������ ������ ����� �� �������!\n" << RESET;
		return;
	}

	int size1 = list[i1].GetSize(), size2 = list[i2].GetSize(); // �������

	int* number1 = new int[size1];
	int* number2 = new int[size2];


	CreateArray(list[i1], list[i2], number1, size1, number2, size2);
	log << "����������� ��������: " << operation << " ��� ������� " << list[i1] << " � " << list[i2] << endl;

	log << "��� ����� � ���������: \n";

	OutStrH(list[i1], log, true);
	log << endl;
	OutStrH(list[i2], log, true);
	log << endl;

	log << "����� ���������� � ������� int ��������" << size1 << " � " << size2 << " ��������������\n";


	int rSize = 0;

	ListH result;

	switch (operation)
	{
	case '+':

		Addition(number1, size1, number2, size2, result, rSize);

		cout << GREEN << "��������� �������� �����: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << result << "\n\n";
		


		log  << "��������� �������� �����: \n\n";
		log << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << result << "\n\n";


		break;

	case '-':

		if (Oless(number1, size1, number2, size2))
		{
			cout << RED << "������ �������� �� �������� �������!!\n" << RESET;
			log << "��������� �� �������� ��������. ������\n";
			return;
		}
		Sub(number1, size1, number2, size2, result, rSize);
		rSize = max(size1, size2);

		cout << GREEN << "��������� ��������� �����: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << setfill(' ') << setw(rSize) << result << "\n\n";

		log << "��������� ��������� �����: \n\n";
		log << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << setfill(' ') << setw(rSize) << result << "\n\n";


		break;

	case '*':
		rSize = size1 + size2;

		cout << GREEN << "��������� ��������� �����: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << setfill(' ') << endl;

		log << "��������� ��������� �����: \n\n";
		log << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << setfill(' ') << endl;


		Multiply(number1, size1, number2, size2, result, rSize);

		rSize = size1 + size2;

		cout << '\t' << setfill('-') << setw(rSize) << "" << endl << setfill(' ')
			<< '\t' << setw(rSize) << result << "\n\n";

		log << '\t' << setfill('-') << setw(rSize) << "" << endl << setfill(' ')
			<< '\t' << setw(rSize) << result << "\n\n";

		break;

	case '/':

		// �������� �� ������ ������� �� ����
		if (size2 == 1 && number2[0] == 0)
		{
			cout << RED << "������ �������� �� �������� �������!!\n" << RESET;
			log << "��������� �� �������� �������. ������.\n";
			return;
		}

		cout << GREEN << "��������� ������� �����: \n\n" << RESET;
		cout << '\t' << list[i1] << "|" << list[i2] << endl;

		log << "��������� ������� �����: \n\n";
		log << '\t' << list[i1] << "|" << list[i2] << endl;


		Division(number1, size1, number2, size2, result, rSize);


		break;
	}

	int position = request[3].Znach() - 1;
	cout << YELLOW;
	if (position >= list.size || position <= 0)
	{
		cout << "��������� �������� � ����� ������!\n";
		log << "��������� �������� � ����� ������!\n";
	}
	else
	{
		cout << "��������� �������� �� " << BLUE << position + 1 << YELLOW << " ����� ������.\n";
		log << "��������� �������� �� " << position + 1 << " ����� ������.\n";
	}
	cout << RESET;
	list.push(result, position);

	cout << setfill(' ') << "";

	CLOSE_LOG
}

// ������ ���� � ��������.
void ReadRequest(ListV& requests)
{
	OPEN_LOG
	ifstream f("Request.txt"); f.unsetf(ios::skipws);
	if (f.eof()) return;

	ListH tempReq;

	int i = 0;
	char t = 0;

	char tempEl[13]{};

	log << "��������� ��������� ���� Request.txt\n";
	while (true)
	{
		f >> t;

		//����� �� ����� ������
		if (t == '\n' || f.eof() || i >= 13)
		{
			log << "����� �� ����� ������\n";
			String Op(1);
			Op[0] = tempEl[0];

			log << "��������� �������� - ��� " << tempEl[0] << "\n";
			tempReq.push_back(Op);

			int k = 2;
			String number(3);

			while (k < i && tempEl[k] != '\0')
			{
				number.SetLen(3);
				int j = 0;
				do
				{

					number[j++] = tempEl[k++];

				} while (tempEl[k] != ' ' && j < 3 && tempEl[k] != '\0');

				number.SetLen(j);
				log << "��������� ����� � ������ ��������� ������ �������.\n";
				tempReq.push_back(number);

				k++;
				number.Clear();


			}

			if (tempReq.size == 3)
			{
				String zero(1);
				zero[0] = '0';
				tempReq.push_back(zero);
			}


			requests.push_back(tempReq);
			log << "��������� ������.\n";

			tempReq.~ListH();

			i = 0;

			for (int l = 0; l < 13; l++) tempEl[l] = '\0';

			if (f.eof())
				break;

		}
		else
		{
			tempEl[i++] = t;
		}

	}
	log << "��������� ������� ��������. ���������� ������ � ��������� � ��������� :" << endl;
	OutPut(requests, log, true);
	CLOSE_LOG
}


// �������� ����� � ��������� �� �����.
void RequestHandler(ListV& list)
{

	ListV requests;

	ReadRequest(requests);

	OPEN_LOG

	while (requests.size > 0)
	{


		log << "����� �������.\n";
		
		cout << CYAN << "\n����� ������ ����� �������:\n" << RESET;
		log << "\n����� ������ ����� �������:\n";

		int k = 0;
		requests.cur = requests.head;

		while (requests.cur != nullptr)
		{
			ListH request = requests.cur->elemH;

			String operation = request[0];
			String n1 = request[1];
			String n2 = request[2];
			++k;
			cout << k << ". ����� ��� ������� " << BLUE << n1 << RESET << " " << operation
				<< " ����� ��� ������� " << BLUE << n2 << RESET << endl;

			log << +k << ". ����� ��� ������� " << n1 << " " << operation
				<< " ����� ��� ������� " << n2 << endl;


			requests.cur = requests.cur->lstNext;
		}
		cout << "0. �����.\n"; log << "0. �����.\n";



		int n = 0;
		cout << "������� �����: "; log << "������� �����: ";
		cin >> n;
		cout << "\n";

		log << "������������ ����: " << n << endl;
		if (n > requests.size || n < 0)
		{
			cout << RED << "\n������ ������� ���!\n" << RESET;
			log  << "\n������ ������� ���!\n";
			continue;
		}
		if (n == 0)
			return;
		else
		{
			
			DoRequest(list, requests[n - 1]);
			requests.pop(n - 1);

			// ����� ������.
			cout << "\n���������� ������: \n";
			list.OutList(cout);
			
			log << "\n���������� ������: \n";
			list.OutList(log);

			log << "���������� ����������� ������ � ���������:\n ";
			OutPut(list, log, true);
			


		}
		/*cout << "\n\n\n";*/


	}



}