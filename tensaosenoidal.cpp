#ifndef TENSAOSENOIDAL
#define TENSAOSENOIDAL

/**
 * Modelo basico de fonte senoidal
 */
#include "senoidal.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoSenoidal : public Senoidal
{

    public:
        /**
         * Construtor
         */
        TensaoSenoidal(string n, int a, int b,
            double a0, double amp, double f,
            double delay, double damp, double p,
            double cic, double t) : Senoidal(n, a, b, a0, amp, f, delay, damp, p, cic, t)
        {
        }
};

#endif