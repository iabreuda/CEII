#ifndef INDUTOR
#define INDUTOR
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Indutor : public Components
{
    public:
        /**
         * Construtor
         */
        Indutor(string n, int a, int b, double v) : Components(n, a, b)
        {
            setIndutancia(v);
        }

        /**
         * Define a corrent no capacitor
         * @param v valor da corrente
         */
        void setPasso(double p)
        {
            passo = p;
        }

        /**
         * Retorna a corrente do  capacitor
         */
        double getPasso()
        {
            return passo;
        }

        /**
         * Define a corrent no indutor
         * @param v valor da corrente
         */
        void setCorrente(double v)
        {
            corrente = v;
        }

        /**
         * Retorna a corrente do indutor
         */
        double getCorrente()
        {

            return corrente;
        }

        /**
         * Define a indutancia no indutor
         * @param v valor da indutacia
         */
        void setIndutancia(double v)
        {
            indutancia = v;
        }

        /**
         * Retorna a inducao do indutor
         */
        double getIndutancia()
        {
            return indutancia;
        }

        /**
         * Retorna corrente que auxiliar
         * para analise nodal modificada
         */
        string getAuxNode()
        {
            return "j" + getNome();
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

            condutancia[getNoA()][pos] += 1;
            condutancia[getNoB()][pos] += -1;
            condutancia[pos][getNoA()] += -1;
            condutancia[pos][getNoB()] += 1;

            /**
             * Valores que sao variaves no instante de tempo inicial e no
             * resto da analise
             */
            if (passo != 0) {
                /**
                 * Tensao no instante de tempo anterior
                 */
                double tensaoRamo = resultado[getNoA()] - resultado[getNoB()];
                /**
                 * Descarta o no Zero uma vez que ele e linearmente dependente
                 */
                if (getNoA() == 0) {
                    tensaoRamo = -1*resultado[getNoB()];
                }
                if (getNoB() == 0) {
                    tensaoRamo = resultado[getNoA()];
                }

                corrente = resultado[pos];

                condutancia[pos][pos] += (2 * getIndutancia()) / passo;
                correntes[pos] += (((2 * getIndutancia()) / passo) * corrente) + tensaoRamo;
            } else {
                condutancia[pos][pos] += 10e9;
            }
        }

    private:
        /**
         * Resistencia associada ao modelo do capacitor
         * no trapezio
         */
        double passo;
        /**
         * Tensao da fonte de tensao
         * associada ao modelo do indutor no trapezio
         */
        double corrente;
        /**
         * valor da indutancia do capacitor
         */
        double indutancia;
};

#endif