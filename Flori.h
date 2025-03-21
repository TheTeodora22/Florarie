#ifndef FLORI_H
#define FLORI_H

#include <cstring>
#include <iostream>

class Floare
{
    private:
        int id;
        int stoc;
        char* tip_floare;
        float pret;
    public:
        //Constructors
        Floare()
        {
            id = 0;
            stoc = 0;
            tip_floare = "";
            pret = 0;
        };
        Floare(int id, int stoc, const char* tip_floare, float pret)
        {
            this->id = id;
            this->stoc = stoc;
            this->tip_floare = new char[strlen(tip_floare) + 1];
            strcpy(this->tip_floare, tip_floare);
            this->pret = pret;
        };

        //Copy constructor
        Floare(Floare &f)
        {
            this->id = f.id;
            this->stoc = f.stoc;
            this->tip_floare = new char[strlen(f.tip_floare) + 1];
            strcpy(this->tip_floare, f.tip_floare);
            this->pret = f.pret;
        };
        // Destructor (Frees Allocated Memory)
        ~Floare() {
            delete[] tip_floare;
        }

        //Get
        int getId() const { return id; }
        int getStoc() const { return stoc; }
        char* getTipFloare() const { return tip_floare; }
        float getPret() const { return pret; }

        // Complex Method: Apply Discount
        void aplicaReducere(float procent) {
        if (procent < 0 || procent > 100) {
            std::cout << "Reducere invalida! Trebuie sa fie intre 0% si 100%." << std::endl;
            return;
        }
        pret -= pret * (procent / 100.0);
        std::cout << "Reducere aplicata: " << procent << "% -> Noul pret: " << pret << " RON" << std::endl;
        }

        void afisare() const {
            std::cout << "Floare #" << id << " - " << tip_floare
                      << " | Pret: " << pret << " RON | Stoc: " << stoc << " bucati" << std::endl;
        }

        void addStoc(int nrBucati) {
            stoc += nrBucati;
        }
};

#endif