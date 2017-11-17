#ifndef RESISTOR
#define RESISTOR
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Resistor : public Components
{
    public:
        /**
         * Construtor
         */
        Resistor(string n, int a, int b, double v) : Components(n, a, b)
        {
        }

        /**
         * Define a resistencia no resistor
         * @param v valor da resistencia
         */
        void setResistencia(double v)
        {
            resistencia = v;
        }

        /**
         * Retorna a resistencia do resistor
         */
        double getResistencia()
        {
            return resistencia;
        }

    private:
        /**
         * Resistencia do resistor
         */
        double resistencia;
};

#endif