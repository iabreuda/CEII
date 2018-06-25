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
            return "jx" + getNome();
        }

        /**
         * Retorna corrente que auxiliar
         * para analise nodal modificada
         */
        string getAuxNode2()
        {
            return "jy" + getNome();
        }

        /**
         * Estanpa da matriz nodal modificada fonte de tensao
         * controlada por corrente
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes       matriz de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
            vector<string>::iterator it;
            vector<string>::iterator it2;

            it = find(nodes.begin(), nodes.end(), getAuxNode());
            auto pos = it - nodes.begin();

            condutancia[getNoC()][pos] += 1;
            condutancia[getNoD()][pos] += -1;
            condutancia[pos][getNoA()] += -1;
            condutancia[pos][getNoB()] += 1;
            condutancia[pos][pos] += getGanho();
        }
};

#endif