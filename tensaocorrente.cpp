#ifndef TENSAOCORRENTE
#define TENSAOCORRENTE
/**
 * Modelo basico componentes de fontes controladas
 */
#include "fontescontroladas.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoCorrente : public FontesControladas
{
    public:
        /**
         * Construtor
         */
        TensaoCorrente(string n, int a, int b, int c, int d, double g) : FontesControladas(n, a, b, c, d, g)
        {
        }
};

#endif