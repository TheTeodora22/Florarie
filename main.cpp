/*
    =====================================
    PROIECT: Gestionare unei Florarii
    =====================================

    >> DESCRIEREA PROBLEMEI <<

    Date de intrare:
    ----------------
    Programul citește informații dintr-un fișier text "input.txt"
					    structurate astfel:
    1. Numărul de tipuri de flori (n) – întreg.
    2. Pentru fiecare floare:
       - ID-ul florii (int)
       - Stocul disponibil (int)
       - Tipul florii (char[], pe linie separată)
       - Prețul unitar (float)
    3. Numărul de comenzi/livrări (nc) – întreg.
    4. Pentru fiecare comandă:
       - ID-ul comenzii (int)
       - Numărul de flori din comandă (int)
       - Pentru fiecare floare din comandă:
	    - ID-ul florii (int)
	    - Cantitatea comandată (int)
       - Destinatarul comenzii (char[], linie separată)
       - Tipul comenzii (0 = PRIMIRE, 1 = LIVRARE)
       - ID-ul livrării (int)
       - Data livrării (char[], format "YYYY-MM-DD")

    Operații posibile:
    ------------------
    1. Operații în clasa Floare:
	- aplicaReducere(float procent) — aplică o reducere la prețul florii.
	- addStoc(int nrBucati) — adaugă un număr de bucăți în stoc.
	- setStoc(int) — setează stocul unei flori.
	- setPret(float) — setează prețul unei flori.
	- setTipFloare(const char*) — actualizează tipul florii.
	- esteInStoc() — verifică dacă floarea are stoc pozitiv.
	- operator<< — permite afișarea detaliilor unei flori.

    2. Operații în clasa Comanda:
	- adaugaFloare(const Floare&, int) — adaugă o floare nouă sau crește
	cantitatea dacă deja există în comandă.
	- eliminaFloare(const Floare&) — elimină o floare din comandă, dacă există.
	- proceseazaComanda() — pentru LIVRARE scade stocul,
	pentru PRIMIRE îl crește.
	- seteazaProcesata() — marchează comanda ca procesată.
	- getFlori(), getCantitati(), getNrFlori() — acces la detaliile comenzii.
	- afisareFloriComanda() — afișează toate florile și cantitățile din comandă.
	- operator<< — permite afișarea detaliilor unei comenzi.

    3. Operații în clasa Livrari:
	- marcheazaLivrata() — procesează comanda și actualizează statusul livrării.
	- actualizeazaData(const char*) — actualizează data livrării.
	- verificaSiActualizeazaDataLivrare() — verifică dacă data e în trecut
	și o actualizează automat.
	- proceseazaLivrare(const char*) — procesează comanda
	și setează data livrării.
	- getComanda(), getDataLivrare(), getEsteLivrata() —
		    acces la detaliile livrării.
	- operator<< — permite afișarea completă a livrării.

*/

#include "Livrari.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
	std::ifstream fin("input.txt");
	if (!fin)
	{
		std::cerr << "Nu s-a putut deschide fisierul input.txt\n";
		return 1;
	}

	int n, nc;
	fin >> n;
	Floare *flori = new Floare[n];

	for (int i = 0; i < n; i++)
	{
		int id, stoc;
		float pret;
		char tip[256];

		fin >> id >> stoc;
		fin.get();
		fin.getline(tip, 256);
		fin >> pret;

		flori[i] = Floare(id, stoc, tip, pret);
	}

	// Testam metodele Floare dupa citire
	for (int i = 0; i < n / 5; i++)
	{
		std::cout << "\n[TEST FLOARE] Initial: " << flori[i] << std::endl;
		flori[i].aplicaReducere(10);
		flori[i].addStoc(5);
		std::cout << "Dupa reducere si adaugare stoc: " << flori[i]
			  << std::endl;
		std::cout << "Este in stoc: " << (flori[i].esteInStoc() ? "Da" : "Nu")
			  << "\n";
	}
	std::cout << "\n[TEST FLOARE] Initial: " << flori[n / 5] << std::endl;
	flori[n / 5].aplicaReducere(99);
	flori[n / 5].setStoc(0);
	std::cout << "Dupa reducere si aplicare stoc: " << flori[n / 5]
		  << std::endl;
	std::cout << "Este in stoc: " << (flori[n / 5].esteInStoc() ? "Da" : "Nu")
		  << "\n";

	fin >> nc;
	Livrari **listaLivrari = new Livrari *[nc];

	for (int i = 0; i < nc; i++)
	{
		int idComanda, nrFlori, idFloare, tipComandaChoice, idLivrare;
		char destinatar[256], dataLivrare[256];

		fin >> idComanda >> nrFlori;

		Floare *floriComanda = new Floare[nrFlori];
		int *cantitatiComanda = new int[nrFlori];

		for (int j = 0; j < nrFlori; j++)
		{
			fin >> idFloare;
			for (int k = 0; k < n; k++)
			{
				if (flori[k].getId() == idFloare)
				{
					floriComanda[j] = flori[k];
					break;
				}
			}
			fin >> cantitatiComanda[j];
		}

		fin.get();
		fin.getline(destinatar, 256);
		fin >> tipComandaChoice;

		TipComanda tipComanda = (tipComandaChoice == 0) ? PRIMIRE : LIVRARE;
		Comanda comanda(idComanda, nrFlori, floriComanda, cantitatiComanda,
				destinatar, false, tipComanda);

		delete[] floriComanda;
		delete[] cantitatiComanda;

		fin >> idLivrare;
		fin.get();
		fin.getline(dataLivrare, 256);

		Livrari *livrare = new Livrari(idLivrare, comanda, dataLivrare, false);

		listaLivrari[i] = livrare;
	}

	std::cout << "\n=== PRIMA TREIME DIN LIVRARI ===\n";
	for (int i = 0; i < nc / 3; i++)
	{
		std::cout << "\n[INAINTE DE LIVRARE] Comanda asociata livrarii " << listaLivrari[i]->getIdLivrare() << ":\n";
		std::cout << listaLivrari[i]->getComanda();
		listaLivrari[i]->getComanda().afisareFloriComanda();
		listaLivrari[i]->marcheazaLivrata();
		std::cout << "\n[DUPA LIVRARE] Comanda actualizata:\n";
		std::cout << listaLivrari[i]->getComanda();
		std::cout << "Florile actualizate: \n";
		listaLivrari[i]->getComanda().afisareFloriComanda();
	}

	std::cout << "\n=== VERIFICARE ULTIMA LIVRARE ===\n";
	Livrari *ultimaLivrare = listaLivrari[nc - 1];

	std::cout << "\n[INAINTE DE VERIFICARE] Livrare ID: "
		  << ultimaLivrare->getIdLivrare() << "\n";
	std::cout << ultimaLivrare->getComanda();
	std::cout << "Data livrare: " << ultimaLivrare->getDataLivrare() << "\n";

	ultimaLivrare->verificaSiActualizeazaDataLivrare();

	std::cout << "\n[DUPA VERIFICARE] Livrare ID: "
		  << ultimaLivrare->getIdLivrare() << "\n";
	std::cout << ultimaLivrare->getComanda();
	std::cout << "Data livrare actualizata: " << ultimaLivrare->getDataLivrare()
		  << "\n";

	std::cout << "\n=== MODIFICARE COMENZI: ADAUGARE / ELIMINARE FLOARE ===\n";

	// Folosim prima comanda (index 0)
	Livrari *livrare1 = listaLivrari[0];
	Comanda comanda1 = livrare1->getComanda();

	std::cout << "\n[Comanda 1] Inainte de adaugare:\n";
	std::cout << comanda1;

	// Adaugam o floare existenta
	comanda1.adaugaFloare(flori[0], 3);
	comanda1.adaugaFloare(flori[5], 10);

	std::cout << "\n[Comanda 1] Dupa adaugarea a 3x "
		  << flori[0].getTipFloare();
	std::cout << " si a 10x " << flori[5].getTipFloare() << ":\n";
	std::cout << comanda1;

	// Folosim o alta comanda (ultima)
	Livrari *livrare2 = listaLivrari[nc - 1];
	Comanda comanda2 = livrare2->getComanda();

	std::cout << "\n[Comanda 2] Inainte de eliminare:\n";
	std::cout << comanda2;

	// Eliminam o floare existenta
	comanda2.eliminaFloare(comanda2.getFlori()[0]);

	std::cout << "\n[Comanda 2] Dupa eliminarea florii \""
		  << flori[1].getTipFloare() << "\":\n";
	std::cout << comanda2;

	delete[] listaLivrari;

	fin.close();
	delete[] flori;
	return 0;
}
