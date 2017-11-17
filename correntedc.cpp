#ifndef CORRENTEDC
#define CORRENTEDC
/**
 * Modelo basico componentes de 4 terminais
 */
#include "dc.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteDC : public DC
{

    public:
        /**
         * Construtor
         */
        CorrenteDC(string n, int a, int b, double v) : DC(n, a, b, v)
        {
        }
};

#endif