#ifndef COMANDA_H
#define COMANDA_H

#include "Floare.h"
#include <iostream>
#include <cstring>

// Definim tipul comenzii: Primire sau Livrare
enum TipComanda
{
    PRIMIRE, // Comandă pentru primirea de flori (se adaugă stocul)
    LIVRARE  // Comandă pentru livrare (se scade stocul)
};

class Comanda
{
private:
    int m_idComanda;
    int m_nrFlori;
    Floare *m_flori;
    int *m_cantitati;
    float m_pret_total;
    char *m_destinatar;
    bool m_status;
    TipComanda m_tipComanda; // Tipul comenzii: primire sau livrare

    // Funcție privată pentru recalcularea totalului comenzii
    void calculeazaTotal()
    {
        m_pret_total = 0;
        for (int i = 0; i < m_nrFlori; ++i)
        {
            m_pret_total += m_flori[i].getPret() * m_cantitati[i];
        }
    }

public:
    // Constructorul implicit
    Comanda()
    {
        this->m_idComanda = 0;
        this->m_nrFlori = 0;
        this->m_flori = nullptr;
        this->m_cantitati = nullptr;
        this->m_pret_total = 0.0f;
        this->m_destinatar = new char[1];
        this->m_destinatar[0] = '\0';
        this->m_status = false;
        this->m_tipComanda = LIVRARE;
    }

    // Constructor cu parametri
    Comanda(int id, int nrFlori, const Floare *flori, const int *cantitati,
            const char *destinatar, bool status, TipComanda tip)
    {
        this->m_idComanda = id;
        this->m_nrFlori = nrFlori;
        this->m_flori = new Floare[nrFlori];
        this->m_cantitati = new int[nrFlori];
        this->m_pret_total = 0.0f;
        this->m_status = status;
        this->m_tipComanda = tip;

        for (int i = 0; i < nrFlori; i++)
        {
            this->m_flori[i] = flori[i];
            this->m_cantitati[i] = cantitati[i];
            this->m_pret_total += flori[i].getPret() * cantitati[i];
        }

        if (destinatar == nullptr)
        {
            this->m_destinatar = new char[1];
            this->m_destinatar[0] = '\0';
        }
        else
        {
            this->m_destinatar = new char[strlen(destinatar) + 1];
            strcpy(this->m_destinatar, destinatar);
        }
    }

    // Constructorul de copiere
    Comanda(int id, int nrFlori, const Floare *flori,
            const int *cantitati, const char *destinatar, TipComanda tip)
    {
        this->m_idComanda = id;
        this->m_nrFlori = nrFlori;
        this->m_flori = new Floare[nrFlori];
        this->m_cantitati = new int[nrFlori];
        this->m_pret_total = 0.0f;
        this->m_status = false;
        this->m_tipComanda = tip;

        for (int i = 0; i < nrFlori; i++)
        {
            this->m_flori[i] = flori[i];
            this->m_cantitati[i] = cantitati[i];
            this->m_pret_total += flori[i].getPret() * cantitati[i];
        }

        if (destinatar == nullptr)
        {
            this->m_destinatar = new char[1];
            this->m_destinatar[0] = '\0';
        }
        else
        {
            this->m_destinatar = new char[strlen(destinatar) + 1];
            strcpy(this->m_destinatar, destinatar);
        }
    }

    // Operator= de copiere
    Comanda &operator=(const Comanda &c)
    {
        if (this != &c)
        {
            delete[] m_destinatar;
            delete[] m_flori;
            delete[] m_cantitati;
            m_idComanda = c.m_idComanda;
            m_nrFlori = c.m_nrFlori;
            m_pret_total = c.m_pret_total;
            m_status = c.m_status;
            m_tipComanda = c.m_tipComanda;
            m_destinatar = new char[strlen(c.m_destinatar) + 1];
            strcpy(m_destinatar, c.m_destinatar);
            m_flori = new Floare[m_nrFlori];
            m_cantitati = new int[m_nrFlori];
            for (int i = 0; i < m_nrFlori; ++i)
            {
                m_flori[i] = c.m_flori[i];
                m_cantitati[i] = c.m_cantitati[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Comanda()
    {
        delete[] m_destinatar;
        delete[] m_flori;
        delete[] m_cantitati;
    }

    // Getteri
    int getIdComanda() const { return m_idComanda; }
    int getNrFlori() const { return m_nrFlori; }
    const Floare *getFlori() const { return m_flori; }
    const int *getCantitati() const { return m_cantitati; }
    float getPretTotal() const { return m_pret_total; }
    const char *getDestinatar() const { return m_destinatar; }
    bool getStatus() const { return m_status; }
    TipComanda getTipComanda() const { return m_tipComanda; }

    // Funcție pentru adăugarea unei flori în comandă
    void adaugaFloare(const Floare &floare, int cantitate)
    {
        for (int i = 0; i < m_nrFlori; ++i)
        {
            if (m_flori[i].getId() == floare.getId())
            {
                m_cantitati[i] += cantitate;
                calculeazaTotal();
                return;
            }
        }
        Floare *tempFlori = new Floare[m_nrFlori + 1];
        int *tempCantitati = new int[m_nrFlori + 1];
        for (int i = 0; i < m_nrFlori; ++i)
        {
            tempFlori[i] = m_flori[i];
            tempCantitati[i] = m_cantitati[i];
        }
        tempFlori[m_nrFlori] = floare;
        tempCantitati[m_nrFlori] = cantitate;
        delete[] m_flori;
        delete[] m_cantitati;
        m_flori = tempFlori;
        m_cantitati = tempCantitati;
        m_nrFlori++;
        calculeazaTotal();
    }

    // Elimină o floare din comandă
    void eliminaFloare(const Floare &floare)
    {
        int index = -1;
        for (int i = 0; i < m_nrFlori; ++i)
        {
            if (m_flori[i].getId() == floare.getId())
            {
                index = i;
                break;
            }
        }
        if (index == -1)
        {
            std::cout << "Floarea \"" << floare.getTipFloare()
                      << "\" nu a fost gasita in comanda.\n";
            return;
        }

        Floare *tempFlori = new Floare[m_nrFlori - 1];
        int *tempCantitati = new int[m_nrFlori - 1];
        int j = 0;
        for (int i = 0; i < m_nrFlori; ++i)
        {
            if (i != index)
            {
                tempFlori[j] = m_flori[i];
                tempCantitati[j] = m_cantitati[i];
                j++;
            }
        }

        delete[] m_flori;
        delete[] m_cantitati;
        m_flori = tempFlori;
        m_cantitati = tempCantitati;
        m_nrFlori--;
        calculeazaTotal();
    }

    void afisareFloriComanda() const
    {
        std::cout << "Flori in comanda:\n";
        for (int i = 0; i < m_nrFlori; ++i)
        {
            std::cout << " - " << m_flori[i] << "\n";
        }
    }

    // Marchează comanda ca procesată (livrată sau primită)
    void seteazaProcesata() { m_status = true; }

    // Funcție de procesare a comenzii
    // Dacă comanda este de primire, se adaugă stocul la fiecare floare.
    // Dacă este de livrare, se scade stocul.
    void proceseazaComanda()
    {
        if (m_tipComanda == PRIMIRE)
        {
            // Pentru fiecare floare se adaugă cantitatea primită
            for (int i = 0; i < m_nrFlori; ++i)
            {
                m_flori[i].addStoc(m_cantitati[i]);
            }
            std::cout << "Comanda de primire a fost procesata. ";
            std::cout << " Stocul a fost marit.\n";
        }
        else if (m_tipComanda == LIVRARE)
        {
            // Pentru fiecare floare se scade cantitatea livrata
            // Se folosește addStoc cu valoare negativă pentru scădere
            for (int i = 0; i < m_nrFlori; ++i)
            {
                m_flori[i].addStoc(-m_cantitati[i]);
            }
            std::cout << "Comanda de livrare a fost procesata.";
            std::cout << " Stocul a fost scazut.\n";
        }
        seteazaProcesata();
    }

    // Suprascriere operator<< pentru afișare
    friend std::ostream &operator<<(std::ostream &out, const Comanda &c)
    {
        out << "Comanda #" << c.m_idComanda << " pentru: " << c.m_destinatar
            << "\n";
        out << "Tip: " << (c.m_tipComanda == PRIMIRE ? "Primire" : "Livrare")
            << "\n";
        for (int i = 0; i < c.m_nrFlori; ++i)
        {
            out << " - " << c.m_flori[i].getTipFloare() << " x" << c.m_cantitati[i]
                << "\n";
        }
        out << "Total: " << c.m_pret_total << " RON\n";
        out << "Status: " << (c.m_status ? "Procesata" : "In asteptare")
            << "\n";
        return out;
    }
};

#endif
