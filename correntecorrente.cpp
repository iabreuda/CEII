#ifndef CORRENTECORRENTE
#define CORRENTECORRENTE
/**
 * Modelo basico componentes de fontes controladas
 */
#include "fontescontroladas.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class CorrenteCorrente : public FontesControladas
{
    public:
        /**
         * Construtor
         */
        CorrenteCorrente(string n, int a, int b, int c, int d, double g) : FontesControladas(n, a, b, c, d, g)
        {
        }

        /**
         * Retorna corrente que auxiliar
         * para analise nodal modificada
         */
        string getAuxNode()
        {
            return "j" + to_string(getNoC()) + "_" + to_string(getNoD());
        }

        /**
         * Estanpa da matriz nodal modificada fonte de corrente
         * controlada por corrente
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes       matriz de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<vector<double> >& correntes,
            vector<string> nodes)
        {
            vector<string>::iterator it;
            it = find(nodes.begin(), nodes.end(), getAuxNode());
            auto pos = it - nodes.begin();

            condutancia[getNoA()][pos] += getGanho();
            condutancia[getNoB()][pos] += -1*getGanho();
            condutancia[getNoC()][pos] += 1;
            condutancia[getNoD()][pos] += -1;
            condutancia[pos][getNoC()] += -1;
            condutancia[pos][getNoD()] += 1;
        }
};

#endif