#ifndef TENSAODC
#define TENSAODC

/**
 * Modelo basico componentes de fonte DC
 */
#include "dc.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoDC : public Dc
{
    public:
        /**
         * Construtor
         */
        TensaoDC(string n, int a, int b, double v) : Dc(n, a, b, v)
        {
        }
};

#endif