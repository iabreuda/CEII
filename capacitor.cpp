#ifndef CAPACITOR
#define CAPACITOR
/**
 * Modelo basico componentes lineares
 */
#include "lineares.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Capacitor : public Lineares
{

    public:
        Capacitor(string n, int a, int b, int v) : Lineares(n, a, b, v)
        {
        }
};

#endif