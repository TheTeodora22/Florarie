#ifndef LIVRARI_H
#define LIVRARI_H
#include "Comanda.h"
#include <iostream>
#include <cstring>
#include <ctime>
class Livrari
{
private:
    int m_idLivrare;
    Comanda m_comandaAsociata;
    char *m_dataLivrare;
    bool m_esteLivrata;

public:
    // Constructorul implicit
    Livrari()
    {
        this->m_idLivrare = 0;
        this->m_comandaAsociata = Comanda();
        this->m_esteLivrata = false;
        this->m_dataLivrare = new char[1];
        this->m_dataLivrare[0] = '\0';
    }

    // Constructor cu parametri
    Livrari(int idLivrare, const Comanda &comanda,
            const char *dataLivrare, bool esteLivrata)
    {
        this->m_idLivrare = idLivrare;
        this->m_comandaAsociata = comanda;
        this->m_esteLivrata = esteLivrata;
        this->m_dataLivrare = new char[strlen(dataLivrare) + 1];
        strcpy(this->m_dataLivrare, dataLivrare);
    }

    // Constructorul de copiere
    Livrari(const Livrari &l)
    {
        this->m_idLivrare = l.m_idLivrare;
        this->m_comandaAsociata = l.m_comandaAsociata;
        this->m_esteLivrata = l.m_esteLivrata;
        this->m_dataLivrare = new char[strlen(l.m_dataLivrare) + 1];
        strcpy(this->m_dataLivrare, l.m_dataLivrare);
    }

    // Operator= de copiere
    Livrari &operator=(const Livrari &l)
    {
        if (this != &l)
        {
            m_idLivrare = l.m_idLivrare;
            m_comandaAsociata = l.m_comandaAsociata;
            m_esteLivrata = l.m_esteLivrata;
            delete[] m_dataLivrare;
            m_dataLivrare = new char[strlen(l.m_dataLivrare) + 1];
            strcpy(m_dataLivrare, l.m_dataLivrare);
        }
        return *this;
    }

    // Destructor
    ~Livrari()
    {
        delete[] m_dataLivrare;
    }

    // Getteri
    int getIdLivrare() const { return m_idLivrare; }
    const Comanda &getComanda() const { return m_comandaAsociata; }
    const char *getDataLivrare() const { return m_dataLivrare; }
    bool getEsteLivrata() const { return m_esteLivrata; }

    // Funcție pentru actualizarea statusului de livrare
    void marcheazaLivrata()
    {
        if (!m_esteLivrata)
        {
            m_comandaAsociata.proceseazaComanda();
            m_comandaAsociata.seteazaProcesata();
            m_esteLivrata = true;
        }
    }

    // Funcție pentru actualizarea datei de livrare
    void actualizeazaData(const char *nouaData)
    {
        delete[] m_dataLivrare;
        m_dataLivrare = new char[strlen(nouaData) + 1];
        strcpy(m_dataLivrare, nouaData);
    }

    void verificaSiActualizeazaDataLivrare()
    {
        // Obține data curentă
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);

        char dataCurenta[11]; // "YYYY-MM-DD" + '\0'
        snprintf(dataCurenta, sizeof(dataCurenta), "%04d-%02d-%02d",
                 1900 + localTime->tm_year,
                 1 + localTime->tm_mon,
                 localTime->tm_mday);

        // Compară lexicografic (formatul ISO e potrivit pentru asta)
        if (strcmp(m_dataLivrare, dataCurenta) < 0)
        {
            std::cout << "Data de livrare era in trecut. "
                      << "Se actualizeaza la data curenta: "
                      << dataCurenta << std::endl;
            actualizeazaData(dataCurenta);
        }
    }

    // Funcție pentru procesarea livrării
    void proceseazaLivrare(const char *dataNoua)
    {
        if (!m_esteLivrata)
        {
            m_comandaAsociata.proceseazaComanda();
            actualizeazaData(dataNoua);
            marcheazaLivrata();
            std::cout << "Livrare procesata cu succes pe data: "
                      << m_dataLivrare << std::endl;
        }
        else
        {
            std::cout << "Livrarea a fost deja procesata." << std::endl;
        }
    }

    // Suprascriere operator<< pentru afișare
    friend std::ostream &operator<<(std::ostream &out, const Livrari &l)
    {
        out << "Livrare #" << l.m_idLivrare << "\n";
        out << "Data livrare: " << l.m_dataLivrare << "\n";
        out << "Status: " << (l.m_esteLivrata ? "Livrata" : "In asteptare");
        out << "\nComanda asociata:\n"
            << l.m_comandaAsociata;
        return out;
    }
};

#endif
