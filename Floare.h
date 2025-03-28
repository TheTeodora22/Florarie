#ifndef FLOARE_H
#define FLOARE_H
#include <iostream>
#include <cstring>

class Floare
{
private:
    int m_id;
    int m_stoc;
    char *m_tipFloare;
    float m_pret;

public:
    // Constanta pentru prețul minim
    static constexpr float MIN_PRET = 1.0f;

    // Constructorul implicit
    Floare()
    {
        this->m_id = 0;
        this->m_stoc = 0;
        this->m_pret = MIN_PRET;
        this->m_tipFloare = new char[1];
        this->m_tipFloare[0] = '\0';
    }

    // Constructor cu parametri
    Floare(int id, int stoc, const char *tip_floare, float pret)
    {
        this->m_id = id;
        this->m_stoc = stoc;
        this->m_pret = pret < MIN_PRET ? MIN_PRET : pret;

        if (tip_floare == nullptr)
        {
            this->m_tipFloare = new char[1];
            this->m_tipFloare[0] = '\0';
        }
        else
        {
            this->m_tipFloare = new char[strlen(tip_floare) + 1];
            strcpy(this->m_tipFloare, tip_floare);
        }
    }

    // Constructorul de copiere
    Floare(const Floare &f)
    {
        this->m_id = f.m_id;
        this->m_stoc = f.m_stoc;
        this->m_pret = f.m_pret;
        this->m_tipFloare = new char[strlen(f.m_tipFloare) + 1];
        strcpy(this->m_tipFloare, f.m_tipFloare);
    }

    // Operator= de copiere
    Floare &operator=(const Floare &f)
    {
        if (this != &f)
        {
            m_id = f.m_id;
            m_stoc = f.m_stoc;
            m_pret = f.m_pret;
            delete[] m_tipFloare;
            m_tipFloare = new char[strlen(f.m_tipFloare) + 1];
            strcpy(m_tipFloare, f.m_tipFloare);
        }
        return *this;
    }

    // Destructor
    ~Floare()
    {
        delete[] m_tipFloare;
    }

    // Getteri
    int getId() const { return m_id; }
    int getStoc() const { return m_stoc; }
    const char *getTipFloare() const { return m_tipFloare; }
    float getPret() const { return m_pret; }

    // Setteri
    void setId(int id)
    {
        m_id = id;
    }

    void setStoc(int stoc)
    {
        m_stoc = stoc;
    }

    void setTipFloare(const char *tip_floare)
    {
        delete[] m_tipFloare;
        if (tip_floare == nullptr)
        {
            m_tipFloare = new char[1];
            m_tipFloare[0] = '\0';
        }
        else
        {
            m_tipFloare = new char[strlen(tip_floare) + 1];
            strcpy(m_tipFloare, tip_floare);
        }
    }

    void setPret(float nouPret)
    {
        if (nouPret < MIN_PRET)
        {
            std::cout << "Pretul nu poate fi mai mic decat "
                      << MIN_PRET << " RON." << std::endl;
            return;
        }
        m_pret = nouPret;
    }

    // Funcție complexă: aplică o reducere procentuală
    void aplicaReducere(float procent)
    {
        if (procent < 0 || procent > 100)
        {
            std::cout << "Reducere invalida! Trebuie sa fie intre 0% si 100%."
                      << std::endl;
            return;
        }
        m_pret -= m_pret * (procent / 100.0f);
        // Asigură-te că prețul nu scade sub valoarea minimă
        if (m_pret < MIN_PRET)
        {
            m_pret = MIN_PRET;
            std::cout << "Pretul a scazut sub valoarea minima" << std::endl;
        }
        std::cout << "Reducere aplicata: " << procent
                  << "% -> Noul pret: " << m_pret << " RON" << std::endl;
    }

    // Funcție de adăugare stoc
    inline void addStoc(int nrBucati)
    {
        m_stoc += nrBucati;
    }

    // Funcție de verificare stoc
    inline bool esteInStoc() const
    {
        return m_stoc > 0;
    }

    // Suprascriere operator<< pentru afișare
    friend std::ostream &operator<<(std::ostream &out, const Floare &f)
    {
        out << "Floare #" << f.m_id << " - " << f.m_tipFloare
            << " | Pret: " << f.m_pret << " RON | Stoc: " << f.m_stoc
            << " bucati";
        return out;
    }
};

#endif
