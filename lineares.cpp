#ifndef LINEARES
#define LINEARES
/**
 * Modelo basico para componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Lineares : public Components
{
    public:
        Lineares(string n, int a, int b, int v) : Components(n, a, b)
        {
            setValor(v);
        }

        void setValor(int v)
        {
            valor = v;
        }

        int getValor()
        {
            return valor;
        }

    private:
        int valor;
};

#endif
