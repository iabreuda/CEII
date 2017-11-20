#ifndef TENSAOCORRENTE
#define TENSAOCORRENTE
/**
 * Modelo basico componentes de fontes controladas
 */
#include "fontescontroladas.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class TensaoCorrente : public FontesControladas
{
    public:
        /**
         * Construtor
         */
        TensaoCorrente(string n, int a, int b, int c, int d, double g) : FontesControladas(n, a, b, c, d, g)
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
         * Retorna corrente que auxiliar
         * para analise nodal modificada
         */
        string getAuxNode2()
        {
            return "j" + to_string(getNoA()) + "_" + to_string(getNoB());
        }

        /**
         * Estanpa da matriz nodal modificada fonte de tensao
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
            vector<string>::iterator it2;

            it = find(nodes.begin(), nodes.end(), getAuxNode());
            it2 = find(nodes.begin(), nodes.end(), getAuxNode2());
            auto pos = it - nodes.begin();
            auto pos2 = it2 - nodes.begin();

            condutancia[getNoA()][pos2] += 1;
            condutancia[getNoB()][pos2] += -1;
            condutancia[getNoC()][pos] += 1;
            condutancia[getNoD()][pos] += -1;
            condutancia[pos][getNoC()] += -1;
            condutancia[pos][getNoD()] += 1;
            condutancia[pos2][getNoA()] += -1;
            condutancia[pos2][getNoB()] += 1;
            condutancia[pos2][pos] += getGanho();
        }
};

#endif