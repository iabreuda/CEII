#ifndef FONTEINDEPENDENTE
#define FONTEINDEPENDENTE
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class FonteIndependente : public Components
{
    public:
        /**
         * Construtor
         */
        FonteIndependente(string n, int a, int b) : Components(n, a, b)
        {
        }

        /**
         * Retorna a valor da fonte
         */
        double getValor()
        {
            return valor;
        }

    private:
        /**
         * Valor da fonte
         */
        double valor = 0;
};

#endif