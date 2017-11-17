#ifndef CAPACITOR
#define CAPACITOR
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Capacitor : public Components
{

    public:
        /**
         * Construtor
         */
        Capacitor(string n, int a, int b, double v) : Components(n, a, b)
        {
            setCapacitancia(v);
        }

        /**
         * Define a resistencia do capacitor
         * @param v valor da resistencia
         */
        void setResistencia(double v)
        {
            resistencia = v;
        }

        /**
         * Retorna a resistencia do  capacitor
         */
        double getResistencia()
        {
            return resistencia;
        }

        /**
         * Define a corrent no capacitor
         * @param v valor da corrente
         */
        void setCorrente(double v)
        {
            corrente = v;
        }

        /**
         * Retorna a corrente do  capacitor
         */
        double getCorrente()
        {
            return corrente;
        }

        /**
         * Define a capacitancia do capacitor
         * @param v valor da capacitancia
         */
        void setCapacitancia(double v)
        {
            capacitancia = v;
        }

        /**
         * Retorna a capacitancia do  capacitor
         */
        double getCapacitancia()
        {
            return capacitancia;
        }

    private:
        /**
         * Resistencia associada ao modelo do capacitor
         * no trapezio
         */
        double resistencia;
        /**
         * Corrente da fonte de corrente
         * associada ao modelo do capacitor no trapezio
         */
        double corrente;
        /**
         * valor da capacitancia do capacitor
         */
        double capacitancia;
};

#endif