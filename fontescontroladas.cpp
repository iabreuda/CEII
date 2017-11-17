#ifndef FONTESCONTROLADAS
#define FONTESCONTROLADAS
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class FontesControladas : public Components4t
{

    public:
        /**
         * Construtor
         */
        FontesControladas(string n, int a, int b, int c, int d, double g) : Components4t(n, a, b, c, d)
        {
        }

        void setGanho(double g)
        {
            ganho = g;
        }

        double getGanho()
        {
            return ganho;
        }

    private:
        double ganho;
};

#endif