#include <string>

class Floare
{
    private:
        int id;
        int stoc;
        std::string tip_floare;
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
        Floare(int id, int stoc, const std::string &tip_floare, float pret)
        {
            this->id = id;
            this->stoc = stoc;
            this->tip_floare = tip_floare;
            this->pret = pret;
        };

        //Copy constructor
        Floare(Floare &f)
        {
            this->id = f.id;
            this->stoc = f.stoc;
            this->tip_floare = f.tip_floare;
            this->pret = f.pret;
        };

        //Get
        int getId() const { return id; }
        int getStoc() const { return stoc; }
        std::string getTipFloare() const { return tip_floare; }
        float getPret() const { return pret; }
};
