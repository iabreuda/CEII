#ifndef CORRENTESENOIDAL
#define CORRENTESENOIDAL
/**
 * Modelo basico componentes de 4 terminais
 */
#include "senoidal.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteSenoidal : public Senoidal
{

    public:
        /**
         * Construtor
         */
        CorrenteSenoidal(string n, int a, int b,
            double a0, double amp, double f,
            double delay, double damp, double p,
            double cic, double t) : Senoidal(n, a, b, a0, amp, f, delay, damp, p, cic, t)
        {
        }
};

#endif