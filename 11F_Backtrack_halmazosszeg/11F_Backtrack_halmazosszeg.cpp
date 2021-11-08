#include <iostream>
#include <vector>

using namespace std;

int Sum_Rek_Gyakorlas(vector<int>& lista, int i=0)
{
	if (i==lista.size())
		return 0;
	
	return lista[i] + Sum_Rek_Gyakorlas(lista, i+1);
}

bool Eldontes(vector<int>& lista, int celszam, int i=0)
{
	if (true)
	{

	}
}

int main()
{
/// egy halmazban lévõ számok összege rekurzívan
	vector<int> v{1,9,5,7,3};
	cout << Sum_Rek_Gyakorlas(v);

	cout << Eldontes(v, 11);


}
