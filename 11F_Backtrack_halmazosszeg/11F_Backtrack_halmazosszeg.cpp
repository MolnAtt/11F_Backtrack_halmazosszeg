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
	bool siker = celszam == 0; //
	bool level = i == lista.size();
	bool remenytelen = celszam < 0; // ilyen nem mindig van.

	if (siker)
		return true;
	if (level || remenytelen)
		return false;

	/** /
	return Eldontes(lista, celszam - lista[i], i + 1) || Eldontes(lista, celszam, i + 1);
	/**/

	/**/
	for (int i = 0; i < 1; i++) // ilyen mindig van! ezért végigpróbálgatás
	{
		bool result = Eldontes(lista, celszam - i*lista[i], i + 1);
		if (result)
			return result; // ezért OKOS végigpróbálgatás!
	}
	return false;
	/**/

}

int main()
{
/// egy halmazban lévõ számok összege rekurzívan
	vector<int> v{1,9,5,7,3};
	cout << Sum_Rek_Gyakorlas(v);

	cout << Eldontes(v, 11);


}
