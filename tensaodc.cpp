#ifndef TENSAODC
#define TENSAODC

/**
 * Modelo basico componentes de fonte DC
 */
#include "dc.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoDC : public DC
{

    public:
        /**
         * Construtor
         */
        TensaoDC(string n, int a, int b, double v) : DC(n, a, b, v)
        {
        }
};

#endif