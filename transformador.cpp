#ifndef TRANSFORMADOR
#define TRANSFORMADOR
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Transformador : public Components4t
{

    public:
        /**
         * Construtor
         */
        Transformador(string n, int a, int b, int c, int d, double n) : Components4t(n, a, b, c, d)
        {
            setN(n);
        }

        /**
         * Define n do transformador
         * @param n valor de N
         */
        void setN(double n)
        {
            N = n;
        }

        /**
         * Retorna n do transformador
         */
        double getN()
        {
            return N;
        }

    private:
        /**
         * Valor n do transformador
         */
        double N;
};

#endif