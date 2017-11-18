#ifndef CORRENTEDC
#define CORRENTEDC

/**
 * Modelo basico componentes de fonte DC
 */
#include "dc.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteDC : public Dc
{
    public:
        /**
         * Construtor
         */
        CorrenteDC(string n, int a, int b, double v) : Dc(n, a, b, v)
        {
        }

        /**
         * Estanpa da matriz nodal modificada fonte de corrente
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<vector<double> >& correntes)
        {
            correntes[getNoA()][0] += -1*getValor();
            correntes[getNoB()][0] += getValor();
        }
};

#endif