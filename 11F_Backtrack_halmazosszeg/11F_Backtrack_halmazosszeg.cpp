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
	bool siker = celszam == 0; // mikor találtuk meg, amit kerestünk
	bool level = i == lista.size(); // mikor fogytak el a részproblémák, és ezért nem találtuk meg, amit kerestünk
	bool remenytelen = celszam < 0; // mikor van az, hogy bár van részprobléma, de nem érdemes továbbkeresni. Ilyen nem mindig van.

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

vector<vector<int>> megoldasok;
vector<int> aktmo;

void Kivalogatas(vector<int>& lista, int celszam, int i = 0)
{
	bool siker = celszam == 0; //
	bool level = i == lista.size();
	bool remenytelen = celszam < 0; // ilyen nem mindig van.

	if (siker)
	{
		megoldasok.push_back(aktmo);
		return;
	}
	if (level || remenytelen)
		return;

	/**/
	for (int be = 1; be >= 0; be--) // végigpróbálgatás
	{
		aktmo[i] = be;
		Kivalogatas(lista, celszam - be * lista[i], i + 1);
	}
	/**/
}


vector<int> legjobbmo;
vector<int> aktualismo;
bool defined;

int osszeg(vector<int>& v)
{
	int sum = 0;
	for (auto& i : v)
	{
		sum += i;
	}
	return sum;
}

bool jobb(vector<int>& egyik, vector<int>& masik)
{
	return osszeg(egyik) > osszeg(masik);
}

void Minimumkereses(vector<int>& lista, int celszam, int i = 0)
{
	bool siker = celszam == 0; //
	bool level = i == lista.size();
	bool remenytelen = celszam < 0 || (defined && osszeg(aktualismo) == osszeg(legjobbmo)); // MOST EZ KIBÕVÜL!!!!!!!!! Ezért fontos külön függvénnyel dolgozni, mert ez így gyorsabb!

	if (siker)
	{
		cerr << "potencialis megoldast talaltam\n";
		if (!defined || jobb(legjobbmo, aktualismo))
		{
			legjobbmo = aktualismo;
			cerr << "jobb megoldast talaltam, csereltem\n";
		}
		defined = true;
		return;
	}
	if (level || remenytelen)
		return;

	/**/
	for (int be = 1; be >= 0; be--) // végigpróbálgatás
	{
		aktualismo[i] = be;
		Minimumkereses(lista, celszam - be * lista[i], i + 1);
	}
	/**/
}


int main()
{
/// egy halmazban lévõ számok összege rekurzívan
	// cout << Sum_Rek_Gyakorlas(v);

	vector<int> v{1,7,5,2,3,9,4};
	int celszam = 11;

	cerr << "teszt: ";
	kiir(v);
	cerr << "ebben keressuk a " << celszam <<" osszeget";

	// ELDÖNTÉS
	cerr << "Van-e ilyen osszegu halmaz?   ";
	cout << Eldontes(v, celszam)<< endl;

	// KERESÉS
	mo.resize(v.size(), -1); // mo = [ -1, -1, -1, -1, -1 ]
	cerr << "Ez itt egy ilyen halmaz:   ";
	bool kereses_eredmenye = Kereses(v, celszam);
	cout << kereses_eredmenye << endl;
	if (kereses_eredmenye)
	{
		kiir(mo);
		kiir2(v, mo);
	}

	//Kivalogatas
	aktmo.resize(v.size(), -1); 
	cerr << "Ez itt az osszes ilyen halmaz:\n";
	Kivalogatas(v, celszam);
	for (auto& megoldas : megoldasok)
	{
		kiir2(v, megoldas);
	}


	//Minimumkeresés
	defined = false;
	legjobbmo.resize(v.size(), -1); 
	aktualismo.resize(v.size(), -1); 
	cerr << "Ez itt a legkisebb ilyen halmaz:\n";
	Minimumkereses(v, celszam);
	kiir2(v, legjobbmo);


	
}
