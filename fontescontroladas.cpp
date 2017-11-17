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
            setGanho(g);
        }

        /**
         * Define o fator multiplicativo da fonte controlada
         * @param g valor do ganho
         */
        void setGanho(double g)
        {
            ganho = g;
        }

        /**
         * Retorna a ganho da fonte controlada
         */
        double getGanho()
        {
            return ganho;
        }

    private:
        /**
         * ganho associado a fonte controlada
         */
        double ganho;
};

#endif