#ifndef CORRENTETENSAO
#define CORRENTETENSAO
/**
 * Modelo basico componentes de fontes controladas
 */
#include "fontescontroladas.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteTensao : public FontesControladas
{
    public:
        /**
         * Construtor
         */
        CorrenteTensao(string n, int a, int b, int c, int d, double g) : FontesControladas(n, a, b, c, d, g)
        {
        }

        /**
         * Estanpa da matriz nodal modificada para fonte de corrente controlada por tensao
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<vector<double> >& correntes)
        {
            condutancia[getNoC()][getNoC()] += getGanho();
            condutancia[getNoD()][getNoD()] += getGanho();
            condutancia[getNoC()][getNoD()] += getGanho();
            condutancia[getNoD()][getNoC()] += getGanho();
        }
};

#endif