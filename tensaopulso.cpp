#ifndef TENSAOPULSO
#define TENSAOPULSO

/**
 * Modelo basico componentes de fontes de pulso
 */
#include "pulso.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoPulso : public Pulso
{

    public:
        /**
         * Construtor
         */
        TensaoPulso(string n, int a, int b,
            double a1, double a2, double delay,
            double tSub, double tDes, double tOn,
            double per, double cic, double t) :
            Pulso(n, a, b, a1, a2, delay, tSub, tDes, tOn, per, cic, t)
        {
        }
};

#endif