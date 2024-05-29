#include <fstream>
#include <sstream>

#include"Methods.h"



using namespace std;

void RequestHandler(ListV& list);


// ������ ���� � ��������.
void ReadRequest(ListV& requests)
{
	ifstream f("Request.txt"); f.unsetf(ios::skipws);
	if (f.eof()) return;

	ListH tempReq;

	int i = 0;
	char t = 0;

	char tempEl[13]{};


	while (true)
	{
		f >> t;

		//����� �� ����� ������
		if (t == '\n' || f.eof() || i >= 13)
		{
			
			String Op(1);
			Op[0] = tempEl[0];

			tempReq.push_back(Op);

			int k = 2;
			String number(3);

			while (k < i && tempEl[k]!='\0')
			{
				number.SetLen(3);
				int j = 0;
				do
				{
					
					number[j++] = tempEl[k++];

				} while (tempEl[k]!=' ' && j<3 && tempEl[k]!='\0');

				number.SetLen(j);
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
}

// ��������������� ������
void ReverseInt(int* number, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		if (i != (size - 1) - i)
		{
			int temp = number[i];
			number[i] = number[(size - 1) - i];
			number[(size - 1) - i] = temp;
		}

	}
}

// ����� ����� int �� �������.
void OutNumber(int* number, int size, char endLine = '\n')
{
	for (int i = 0; i < size; i++)
	{
		std::cout << number[i];
	}
	std::cout << endLine;
}


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

void RemoveZeroes(int*& number, int& size)
{
	while (size > 1 && number[0] == 0) {
		number++;
		size--;
	}
}

// ����� �����
void Addition(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	sizelr = max(sizel1, sizel2) + 1;
	int* numberR = new int[sizelr];
	// ������ �������� �������
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);

	// ��� �����.
	/*cout << '\n';
	OutNumber(number1, sizel1);
	OutNumber(number2, sizel2);*/


	int carry = 0, total = 0;
	for (int i = 0; i < sizelr; i++)
	{
		// ������� �����, ����� �� ����� �������� �� ����� �������.
		int digit1 = i < sizel1 ? number1[i] : 0;
		int digit2 = i < sizel2 ? number2[i] : 0;

		// �������
		total = digit1 + digit2;

		// ���� �����+ ������� ������ 9 �� � ����� ������ ���� ����� ���� ��� �� ������ �����+�������
		numberR[i] = total + carry > 9 ? (total + carry) % 10 : total + carry;

		// ��������� �������
		carry = (total + carry) / 10;

	}

	// ������� �������� ���� ���� �� ����.
	if (numberR[sizelr - 1] == 0)
		sizelr--;
	

	// �������������� ����� �������
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);
	ReverseInt(numberR, sizelr);

	

	//OutNumber(number1, sizel1, '+');
	//OutNumber(number2, sizel2, '=');

	//OutNumber(numberR, sizelr);

	// ��������� ��������� � ������ result

	MakeList(result, numberR, sizelr);


	delete[] numberR;
}

// ==
bool Oequal(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (sizel1 != sizel2)
		return false;
	else
	{
		for (int i = 0; i < sizel1; i++)
		{
			if (number1[i] != number2[i])
				return false;
		}
		return true;
	}
}

bool Oless(int* number1, const int sizel1, int* number2, const int sizel2)
{
	if (Oequal(number1, sizel1, number2, sizel2))
		return false;
	else
	{
		if (sizel1 != sizel2)
			return sizel1 < sizel2;
		else
		{
			for (int i = 0; i < sizel1; i++)
			{
				if (number1[i] != number2[i])
					return number1[i] < number2[i];
			}
		}

	}
}

bool Obig(int* number1, const int sizel1, int* number2, const int sizel2) // >=
{
	if (!Oless(number1, sizel1, number2, sizel2)) // ������ ��� >=
	{
		
		return true;
		
	}

	return false;
}

// ���������
void Sub(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	sizelr = max(sizel1, sizel2);
	int* numberR = new int[sizelr];

	// ������ �������� �������
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);

	// ������� ������ ������� ����� �� ������ ������
	int* number1copy = new int[sizel1];
	for (int i = 0; i < sizel1; i++)
	{
		number1copy[i] = number1[i];
	}

	// ���������� ���� ������.

	int carry = 0;
	for (int i = 0; i < sizelr; i++)
	{
		// ������� �����, ����� �� ����� �������� �� ����� �������.
		int digit1 = i < sizel1 ? number1copy[i] : 0;
		int digit2 = i < sizel2 ? number2[i] : 0;

		// �������
		int total = digit1 - digit2;

		if (total < 0)
		{
			number1copy[i + 1] -= 1;
			total += 10;
		}
		
		numberR[i] = total;
	}

	int i = sizelr;
	while (numberR[i-1] == 0)
	{
		sizelr--;
		i--;
	}

	/*OutNumber(number1, sizel1);*/

	// �������������� ����� �������
	ReverseInt(number1, sizel1);
	ReverseInt(number2, sizel2);
	ReverseInt(numberR, sizelr);

	


	/*OutNumber(number1, sizel1, '-');
	OutNumber(number2, sizel2, '=');

	OutNumber(numberR, sizelr);*/

	// ��������� ��������� � ������ result

	MakeList(result, numberR, sizelr);

	/*OutNumber(numberR, sizelr);*/

	MakeList(result, numberR, sizelr);

	delete[] number1copy;
	delete[] numberR;
}

// ���������
void Multiply(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result, int& sizelr)
{
	// ���� �������� �� 0.
	if (sizel1 == 1 && number1[0] == 0 || sizel2 == 1 && number2[0] == 0)
	{
		int* zero = new int[1];
		zero[0] = 0;
		MakeList(result, zero, 1);
		return;
	}


	// ��������� ������ ��� ���������� ���������.
	sizelr = sizel1 + sizel2;
	int* numberR = new int[sizelr]();
	// ��� ������������� �����������.
	int promSize = sizel1 + 1;
	const int begsize = promSize;
	int* promNumber = new int[promSize];
	for (int i = 0; i < sizel1+1; i++)
	{
		promNumber[i] = numberR[i];
	}
	promNumber[promSize-1] = 0;

	int w = sizelr; // �����
	// ������� ������������� ����������.
	for (int i = sizel2 - 1; i >= 0; i--) // number 2
	{
		// ����������� ���������
		int carry = 0;
		int all = promSize-1;
		for (int j = sizel1 - 1; j >= 0; j--) // number 1
		{
			int cur = number2[i] * number1[j] + promNumber[all] + carry;

			promNumber[all--] = cur % 10;

			carry = cur / 10;

		}
		
		promNumber[all] += carry;
		

		// ����� �����.
		RemoveZeroes(promNumber, promSize);
		
		if (promNumber[0] != 0)
		{
			ListH tempLst;
			MakeList(tempLst, promNumber, promSize);

			cout << '\t' << setw(w) << tempLst << endl;

			tempLst.~ListH();
		}
		w--;

		// ������� �����.
		for (int i = 0; i < begsize; i++)
		{
			promNumber[i] = 0;
		}
		promSize = begsize;

	}


	
	
	for (int i = sizel2-1; i >= 0; i--) // number 2
	{
		int carry = 0;
		for (int j = sizel1 - 1; j >= 0; j--) // number 1
		{
			int cur = number2[i] * number1[j] + numberR[i + j + 1] + carry;


			numberR[i + j + 1] = cur % 10;

			carry = cur / 10;

		}
		
		if (carry != 0)
		{
			numberR[i] += carry;
		}
	}

	// �������� ������� �����.
	RemoveZeroes(numberR, sizelr);


	
	MakeList(result, numberR, sizelr);

	delete[] numberR;


}

// ����� ��������� �����, �������������� ���������
int CompareNumbers(int* number1, int size1, int* number2, int size2)
{
	if (size1 > size2) return 1;
	if (size1 < size2) return -1;
	for (int i = size1 - 1; i >= 0; i--) {
		if (number1[i] > number2[i]) return 1;
		if (number1[i] < number2[i]) return -1;
	}
	return 0;
}

// ����� ��������� ������ ����� �� �������, �������������� ���������
void SubtractNumbers(int* number1, int& size1, int* number2, int size2)
{
	for (int i = 0; i < size2; i++) {
		number1[i] -= number2[i];
		if (number1[i] < 0) {
			number1[i] += 10;
			number1[i + 1]--;
		}
	}
	for (int i = size2; i < size1; i++) {
		if (number1[i] < 0) {
			number1[i] += 10;
			number1[i + 1]--;
		}
	}
	while (size1 > 1 && number1[size1 - 1] == 0) {
		size1--;
	}
}



// ����� ��� ������ �����.
std::string Out(int* number, int size)
{
	std::ostringstream oss;
	for (int i = 0; i < size; i++) {
		oss << number[i];
	}
	return oss.str();
}

// ������� ��������� number2 �� number1 (number1 >= number2)
void Subtract(int* number1, int size1, int* number2, int size2)
{
	for (int i = 0; i < size2; i++) {
		number1[size1 - size2 + i] -= number2[i];
		if (number1[size1 - size2 + i] < 0) {
			number1[size1 - size2 + i] += 10;
			number1[size1 - size2 + i - 1] -= 1;
		}
	}
	// ��������� ������
	for (int i = size1 - size2 - 1; i >= 0; i--) {
		if (number1[i] < 0) {
			number1[i] += 10;
			number1[i - 1] -= 1;
		}
	}
}

void MultiplyByNumber(int* number, int& size, int n)
{
	int result_size = size + 1; // ��������� ����� ���� �� 1 ������ ������ ��������� �����
	int* result = new int[result_size]();

	int carry = 0;
	for (int i = size - 1; i >= 0; i--) {
		int product = number[i] * n + carry;
		result[i + 1] = product % 10;
		carry = product / 10;
	}
	result[0] = carry;

	RemoveZeroes(result, result_size);

	delete[] number;
	
	number = result;

	size = result_size;

}

// �������
void Division(int* number1, const int sizel1, int* number2, const int sizel2, ListH& result_list, int& sizelr)
{
	// �������� �� ������ ������� �� ����
	if (sizel2 == 1 && number2[0] == 0) {
		throw std::invalid_argument("Division by zero");
	}

	// ������� ������� ���� �� �������� � ��������
	RemoveZeroes(number1, const_cast<int&>(sizel1));
	RemoveZeroes(number2, const_cast<int&>(sizel2));

	// ���� ������� ������ ��������, ��������� - 0
	if (Oless(number1, sizel1, number2, sizel2)) {
		int* zero = new int[1];
		zero[0] = 0;
		MakeList(result_list, zero, 1);
		return;
	}


	// ��������� ������ ��� ����������
	sizelr = sizel1 - sizel2 + 1;
	int* result = new int[sizelr]();


	int* tempN = new int[sizel1]();
	int tempN_size = 0;

	int p = 0; // �� ����� ������� � 1 �����.
	for (int i = 0; i < sizelr; i++)
	{
		// �������� �����, �� ������� �������.
		
		while (Oless(tempN, tempN_size, number2, sizel2))
		{
			tempN[p] = number1[p];
			p++;
			tempN_size++;
		}

		// �������� �������� ����� ������ ����� ��� �������� �����.

		cout << setw(sizel1 + i) << left << Out(tempN, tempN_size) << "|" << endl;
		if (i != 0)
			cout << setw(sizel1 + 1) << setfill('-') << "" << setfill(' ') << endl;



		for (int c = 1; c <= 9; c++)
		{

			int* product = new int[tempN_size + 1]();
			for (int i = 0; i < tempN_size; i++)
			{
				product[i] = tempN[i];
			}

			int product_size = tempN_size + 1;
			
			MultiplyByNumber(product, product_size, c);

			if(Obig(tempN, tempN_size, product, product_size)) 
			{
				if (!Oequal(product, product_size, tempN, tempN_size))
				{
					// ��� ����� ��� ����������.
					c--;
					for (int i = 0; i < tempN_size; i++)
					{
						product[i] = tempN[i];
					}
					MultiplyByNumber(product, product_size, c);
				}
				

				Subtract(tempN, tempN_size, product, product_size);
				RemoveZeroes(tempN, tempN_size);
				result[i] = c;
				delete[] product;
				break;
			}
			
			


		}

	}






	delete[] result;

}






void DoRequest(ListV& list, ListH& request)
{
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

	int rSize = 0;

	ListH result;

	switch (operation)
	{
	case '+':
		
		Addition(number1, size1, number2, size2, result, rSize);

		cout << GREEN <<"��������� �������� �����: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
			<< '\t' << setw(rSize) << list[i2] << endl
			<< '\t' << setfill('-') << setw(rSize) << "" << endl
			<< '\t' << result << "\n\n";

		break;

	case '-':

		if (Oless(number1, size1, number2, size2))
		{
			cout << "������ �������� �� �������� �������!!\n";
			return;
		}
		Sub(number1, size1, number2, size2, result, rSize);
		rSize = max(size1, size2);
		cout << GREEN << "��������� ��������� �����: \n\n" << RESET;
		cout << '\t' << setw(rSize) << list[i1] << endl
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
	
		Multiply(number1, size1, number2, size2, result, rSize);

		rSize = size1 + size2;

		cout << '\t' << setfill('-') << setw(rSize) << "" << endl << setfill(' ')
			<< '\t' << setw(rSize) << result << "\n\n";

		break;

	case '/':

		cout << GREEN << "��������� ������� �����: \n\n" << RESET;
		cout << '\t' << list[i1] << "|" << list[i2] << endl;


		Division(number1, size1, number2, size2, result, rSize);


		break;
	}

	int position = request[3].Znach() - 1;
	cout << YELLOW;
	if (position >= list.size || position <= 0)
	{
		cout << "��������� �������� � ����� ������!\n";
	}
	else
	{
		cout << "��������� �������� �� " << BLUE << position + 1 << YELLOW << " ����� ������.\n";
	}
	cout << RESET;
	list.push(result, position);


}

// �������� ����� � ��������� �� �����.

void RequestHandler(ListV& list)
{

	ListV requests;

	ReadRequest(requests);

	while (requests.size>0)
	{


		// ����� �������.
		cout << CYAN << "\n����� ������ ����� �������:\n" << RESET;
		int k = 0;
		requests.cur = requests.head;
		
		while (requests.cur!=nullptr)
		{
			ListH request = requests.cur->elemH;

			String operation = request[0];
			String n1 = request[1];
			String n2 = request[2];
			cout << ++k << ". ����� ��� ������� " << BLUE << n1 << RESET << " " << operation 
				<< " ����� ��� ������� " << BLUE << n2  << RESET << endl;


			requests.cur = requests.cur->lstNext;
		}
		cout << "0. �����.\n";
		


		int n = 0;
		cout << "������� �����: ";
		cin >> n;
		cout << "\n";

		if (n > requests.size || n<0)
		{
			cout << "\n������ ������� ���!\n";
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
			
			
		}
		/*cout << "\n\n\n";*/
		

	}


	
}



int main()
{
	setlocale(0, "Rus");

	ifstream file("Input.txt");
	ifstream request("Request.txt"); request.unsetf(ios::skipws);
	ofstream ofile("Output.txt");
	ofstream result("Result.txt");

	ListV list;

	Inf(list, file, ofile);
	OutPut(list, ofile);

	cout << "���� ������� ������.\n\n";
	cout << "���������� ������: \n";
	list.OutList(cout);


	RequestHandler(list);

	file.close(); request.close(); ofile.close(); result.close();
}