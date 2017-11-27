#ifndef CORRENTESENOIDAL
#define CORRENTESENOIDAL

/**
 * Modelo basico de fonte senoidal
 */
#include "senoidal.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteSenoidal : public Senoidal
{

    public:
        /**
         * Construtor
         */
        CorrenteSenoidal(string n, int a, int b,
            double a0, double amp, double f,
            double delay, double damp, double p,
            double cic, double t) : Senoidal(n, a, b, a0, amp, f, delay, damp, p, cic, t)
        {
        }

        /**
         * Estanpa da matriz nodal modificada fonte de corrente
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
            correntes[getNoA()] += -1*getValor();
            correntes[getNoB()] += getValor();
        }
};

#endif