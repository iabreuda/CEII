#ifndef INDUTOR
#define INDUTOR
/**
 * Modelo basico componentes lineares
 */
#include "lineares.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Indutor : public Lineares
{
    public:
        Indutor(string n, int a, int b, int v) : Lineares(n, a, b, v)
        {
        }
};

#endif