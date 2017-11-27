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
            setResistencia(v);
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

        /**
         * Estanpa da matriz nodal modificada para resistor
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
            condutancia[getNoA()][getNoA()] += 1/getResistencia();
            condutancia[getNoB()][getNoB()] += 1/getResistencia();
            condutancia[getNoA()][getNoB()] += -1/getResistencia();
            condutancia[getNoB()][getNoA()] += -1/getResistencia();
        }

    private:
        /**
         * Resistencia do resistor
         */
        double resistencia;
};

#endif