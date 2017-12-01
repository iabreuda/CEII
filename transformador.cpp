#ifndef TRANSFORMADOR
#define TRANSFORMADOR
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Transformador : public Components4t
{

    public:
        /**
         * Construtor
         */
        Transformador(string n, int a, int b, int c, int d, double param) : Components4t(n, a, b, c, d)
        {
            setN(param);
        }

        /**
         * Define n do transformador
         * @param n valor de N
         */
        void setN(double param)
        {
            N = param;
        }

        /**
         * Retorna n do transformador
         */
        double getN()
        {
            return N;
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
         * Estanpa da matriz nodal modificada fonte de tensao
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
            it = find(nodes.begin(), nodes.end(), getAuxNode());
            auto pos = it - nodes.begin();

            condutancia[getNoA()][pos] += -1*getN();
            condutancia[getNoB()][pos] += getN();
            condutancia[getNoC()][pos] += 1;
            condutancia[getNoD()][pos] += -1;
            condutancia[pos][getNoA()] += getN();
            condutancia[pos][getNoB()] += -1*getN();
            condutancia[pos][getNoC()] += -1;
            condutancia[pos][getNoD()] += 1;
        }

    private:
        /**
         * Valor n do transformador
         */
        double N;
};

#endif