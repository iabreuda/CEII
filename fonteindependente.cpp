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
         * Valor da fonte
         */
        double valor;

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

        /**
         * Funcao abstrata que deve ser declarada nas classes filhas
         */
        virtual void setValor() {};
};

#endif