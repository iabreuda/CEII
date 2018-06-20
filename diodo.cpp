#ifndef DIODO
#define DIODO
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Diodo : public Components
{
    public:
        /**
         * Construtor
         */
        Diodo(string n, int a, int b, double is, double nvt) : Components(n, a, b)
        {
            setLinearidade(false);
            setCorrenteReversa(is);
            setTensaoTemp(nvt);
        }

        /**
         * Define a corrente reversao no diodo
         * @param is valor da corrente reversa
         */
        void setCorrenteReversa(double is)
        {
            correntReversa = is;
        }

        /**
         * Define a tensao que varia com a temperatura
         * @param ntv taxa de variacao
         */
        void setTensaoTemp(double nvt)
        {
            tensaoTemp = nvt;
        }

        /**
         * Retorna a corrente reversa do diodo
         */
        double getCorrenteReversa()
        {
            return correntReversa;
        }

        /**
         * Retorna o parametro vt do diodo
         */
        double getTensaoTemp()
        {
            return tensaoTemp;
        }

        /**
         * Pega a resistencia no ponto de operacao pedido
         */
        double getResistencia(double tensao)
        {
            if (tensao > 0.8) {
                tensao = 0.8; // Limita o valor da tensao em 0.8
            }
            return 1/((getCorrenteReversa() * exp(tensao / getTensaoTemp())) / getTensaoTemp());
        }

        /**
         * Corrente de acordo com a tensao no ponto de operacao
         */
        double getCorrente(double tensao)
        {
            if (tensao > 0.8) {
                tensao = 0.8; // Limita o valor da tensao em 0.8
            }
            return (getCorrenteReversa() * (exp(tensao / getTensaoTemp()) - 1)) - (1/getResistencia(tensao) * tensao);
        }

        /**
         * Estampa da matriz nodal modificada para um diodo
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
            /**
             * Pega a tensao no ramo no instante de tempo anterior
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
            condutancia[getNoA()][getNoA()] += 1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoB()] += 1/getResistencia(tensaoRamo);
            condutancia[getNoA()][getNoB()] += -1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoA()] += -1/getResistencia(tensaoRamo);

            correntes[getNoA()] += -1*getCorrente(tensaoRamo);
            correntes[getNoB()] += getCorrente(tensaoRamo);
        }

        /**
         * Desestampa da matriz nodal modificada para um diodo
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes        matris de nos
         */
        void desestampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<double> resultado)
        {
            /**
             * Pega a tensao no ramo no instante de tempo anterior
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

            condutancia[getNoA()][getNoA()] += -1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoB()] += -1/getResistencia(tensaoRamo);
            condutancia[getNoA()][getNoB()] += 1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoA()] += 1/getResistencia(tensaoRamo);

            correntes[getNoA()] += getCorrente(tensaoRamo);
            correntes[getNoB()] += -1*getCorrente(tensaoRamo);
        }


    private:
        /**
         * corrente Reversa
         */
        double correntReversa;
        /**
         * Tensao Vt
         */
        double tensaoTemp;
};

#endif