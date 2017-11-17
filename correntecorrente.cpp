#ifndef CORRENTECORRENTE
#define CORRENTECORRENTE
/**
 * Modelo basico componentes de fontes controladas
 */
#include "fontescontroladas.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteCorrente : public FontesControladas
{
    public:
        /**
         * Construtor
         */
        CorrenteCorrente(string n, int a, int b, int c, int d, double g) : FontesControladas(n, a, b, c, d, g)
        {
        }
};

#endif