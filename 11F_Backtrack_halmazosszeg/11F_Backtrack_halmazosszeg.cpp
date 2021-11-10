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

	/** / // ez itt a szép
	return Eldontes(lista, celszam - lista[i], i + 1) || Eldontes(lista, celszam, i + 1);
	/**/

	/**/ // ez itt az általánosabb, amin jobban látszanak a dolgok
	for (int be = 0; be <= 1; be++) // ilyen mindig van! ezért végigpróbálgatás
	{
		bool result = Eldontes(lista, celszam - be*lista[i], i + 1);
		if (result)
			return result; // ezért OKOS végigpróbálgatás!
	}
	return false;
	/**/
}

vector<int> mo;

bool Kereses(vector<int>& lista, int celszam, int i = 0)
{
	bool siker = celszam == 0; //
	bool level = i == lista.size();
	bool remenytelen = celszam < 0; // ilyen nem mindig van.

	if (siker)
		return true;
	if (level || remenytelen)
		return false;

	/**/ 
	for (int be = 0; be <= 1; be++) // ilyen mindig van! ezért végigpróbálgatás
	{
		mo[i] = be;
		bool result = Kereses(lista, celszam - be * lista[i], i + 1);
		if (result)
			return result; // ezért OKOS végigpróbálgatás!
	}
	return false;
	/**/
}



void kiir(const vector<int>& v)
{
	cout << "[ ";
	for (auto& i : v)
	{
		cout << i << " ";
	}
	cout << "]\n";
}

void kiir2(const vector<int>& v, const vector<int>& mo)
{
	cout << "{ ";
	for (int i = 0; i < v.size(); i++)
	{
		if (mo[i] == 1)
		{
			cout << v[i] << " ";
		}
	}
	cout << "}\n";
}

int main()
{
/// egy halmazban lévõ számok összege rekurzívan
	vector<int> v{9,1,7,5,3};
	// cout << Sum_Rek_Gyakorlas(v);

	cerr << "teszt: ";
	kiir(v);

	// ELDÖNTÉS
	cerr << "Van-e ilyen osszegu halmaz?   ";
	cout << Eldontes(v, 11)<< endl;

	// KERESÉS
	mo.resize(v.size(), -1); // mo = [ -1, -1, -1, -1, -1 ]
	cerr << "Ez itt egy ilyen halmaz:   ";
	bool kereses_eredmenye = Kereses(v, 11);
	cout << kereses_eredmenye << endl;
	if (kereses_eredmenye)
	{
		kiir(mo);
		kiir2(v, mo);
	}


	

}
