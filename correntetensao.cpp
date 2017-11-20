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
         * @param nodes        matris de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<vector<double> >& correntes,
            vector<string> nodes)
        {
            condutancia[getNoA()][getNoC()] += getGanho();
            condutancia[getNoA()][getNoD()] += -1*getGanho();
            condutancia[getNoB()][getNoC()] += -1*getGanho();
            condutancia[getNoB()][getNoD()] += getGanho();
        }
};

#endif