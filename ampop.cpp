#ifndef AMPOP
#define AMPOP
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class AmpOp : public Components4t
{

    public:
        /**
         * Construtor
         */
        AmpOp(string n, int a, int b, int c, int d) : Components4t(n, a, b, c, d)
        {
        }
};

#endif