#ifndef CORRENTEDC
#define CORRENTEDC

/**
 * Modelo basico componentes de fonte DC
 */
#include "dc.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteDC : public Dc
{
    public:
        /**
         * Construtor
         */
        CorrenteDC(string n, int a, int b, double v) : Dc(n, a, b, v)
        {
        }
};

#endif