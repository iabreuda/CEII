#ifndef RESISTOR
#define RESISTOR
/**
 * Modelo basico componentes lineares
 */
#include "lineares.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Resistor : public Lineares
{
    public:
        Resistor(string n, int a, int b, int v) : Lineares(n, a, b, v)
        {
        }
};

#endif