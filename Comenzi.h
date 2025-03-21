#ifndef COMANDA_H
#define COMANDA_H

#include "Flori.h"
#include <iostream>
#include <cstring>
class Comanda
{
    private:
        int id_comanda;
        int nrFlori;
        Floare* flori;
        int* cantitati;
        float pret_total;
        char* destinatar;
        bool status;
    public:
        //Constructors
        Comanda()
        {
            id_comanda = 0;
            nrFlori = 0;
            flori = nullptr;
            cantitati = nullptr;
            pret_total = 0;
            destinatar = nullptr;
            status = false;
        };
        Comanda(int id_comanda, int nrFlori, Floare* flori, int* cantitati, float pret_total, const char* destinatar, bool status)
        {
            this->id_comanda = id_comanda;
            this->nrFlori = nrFlori;
            this->status = status;
            this->destinatar = new char[strlen(destinatar) + 1];
            strcpy(this->destinatar, destinatar);

             // Allocate memory for flowers and quantities
            this->flori = new Floare[nrFlori];
            this->cantitati = new int[nrFlori];

            for (int i = 0; i < nrFlori; ++i) 
            {
                this->flori[i] = flori[i];  // Copy each flower
                this->cantitati[i] = cantitati[i]; // Copy the corresponding quantity
            }
            calculeazaTotal();
        };

        //Copy constructor
        Comanda(Comanda &c)
        {
            this->id_comanda = c.id_comanda;
            this->nrFlori = c.nrFlori;
            this->flori = new Floare[nrFlori];
            this->cantitati = new int[nrFlori];

            for (int i = 0; i < nrFlori; ++i) 
            {
            this->flori[i] = c.flori[i];
            this->cantitati[i] = c.cantitati[i];
            }
            this->pret_total = c.pret_total;
            this->destinatar = new char[strlen(c.destinatar) + 1];
            strcpy(this->destinatar, c.destinatar);
            this->status = c.status;
        };

        //Get
        int getIdComanda() const { return id_comanda; }
        int getnrFlori() const { return nrFlori; }
        Floare* getFlori() const { return flori; }
        int* getCantitati() const { return cantitati; }
        float getPretTotal() const { return pret_total; }
        char* getDestinatar() const { return destinatar; }
        bool getStatus() const { return status; }

        //Destructor
        ~Comanda()
        {
            if (destinatar) delete[] destinatar;
            if (flori) delete[] flori;
            if (cantitati) delete[] cantitati;
        }
        //Functii complexe
        void adaugaFloare(const Floare& floare, int nrFlori) {
            for (int i = 0; i < nrFlori; ++i) {
                if (strcmp(flori[i].getTipFloare(), floare.getTipFloare()) == 0) {
                    cantitati[i] += nrFlori;
                    calculeazaTotal();
                    return;
                }
            }
    
            Floare* tempFlori = new Floare[nrFlori + 1];
            int* tempCantitati = new int[nrFlori + 1];
    
            for (int i = 0; i < nrFlori; ++i) {
                tempFlori[i] = flori[i];
                tempCantitati[i] = cantitati[i];
            }
    
            tempFlori[nrFlori] = floare;
            tempCantitati[nrFlori] = nrFlori;
    
            delete[] flori;
            delete[] cantitati;
    
            flori = tempFlori;
            cantitati = tempCantitati;
            nrFlori++;
    
            calculeazaTotal();
        }
        void calculeazaTotal() {
            pret_total = 0;
            for (int i = 0; i < nrFlori; ++i) {
                pret_total += flori[i].getPret() * cantitati[i];
            }
        }
        void seteazaLivrat() { status = true; }
        void afisare() const {
            std::cout << "Comanda #" << id_comanda << " pentru: " << destinatar << std::endl;
            for (int i = 0; i < nrFlori; ++i) {
                std::cout << "- " << flori[i].getTipFloare()
                          << " x" << cantitati[i]
                          << " (Pret per buc: " << flori[i].getPret() << " RON)"
                          << std::endl;
            }
            std::cout << "Total: " << pret_total << " RON" << std::endl;
            std::cout << "Status: " << (status ? "Livrată" : "În așteptare") << std::endl;
        }
};

#endif
