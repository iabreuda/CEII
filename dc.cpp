#ifndef DC
#define DC
/**
 * Modelo basico de fontes independentes
 */
#include "fonteindependente.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class DC : public FonteIndependente
{
    public:
        /**
         * Construtor
         */
        DC(string n, int a, int b, double v) : FonteIndependente(n, a, b)
        {
            setValor(v);
        }

        /**
         * Metodo abstrato de fontes independents
         * que determina o valor da fonte
         * @param v valor da valor
         */
        void setValor(double v)
        {
            valor = v;
        }
};

#endif