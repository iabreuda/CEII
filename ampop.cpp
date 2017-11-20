#ifndef AMPOP
#define AMPOP
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class AmpOp : public Components4t
{

    public:
        /**
         * Construtor
         */
        AmpOp(string n, int a, int b, int c, int d) : Components4t(n, a, b, c, d)
        {
        }

        /**
         * Retorna corrente que auxiliar
         * para analise nodal modificada
         */
        string getAuxNode()
        {
            return "j" + to_string(getNoA()) + "_" + to_string(getNoB());
        }

        /**
         * Estanpa da matriz nodal modificada amp op
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

            condutancia[getNoA()][pos] += 1;
            condutancia[getNoB()][pos] += -1;
            condutancia[pos][getNoC()] += 1;
            condutancia[pos][getNoD()] += -1;
        }
};

#endif