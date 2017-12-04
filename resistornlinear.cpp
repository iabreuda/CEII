#ifndef RESISTORNLINEAR
#define RESISTORNLINEAR
/**
 * Modelo basico de componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class ResistorNLinear : public Components
{
    public:
        /**
         * Construtor
         */
        ResistorNLinear(string n, int a, int b,
            double x1, double y1,
            double x2, double y2,
            double x3, double y3,
            double x4, double y4) : Components(n, a, b)
        {
            setLinearidade(false);
            setPonto1(x1,y1);
            setPonto2(x2,y2);
            setPonto3(x3,y3);
            setPonto4(x4,y4);
        }

        /**
         * Define os pontos x,y do ponto 1 no resistor
         * linear
         * @param x1 valor da tensao
         * @param y1 valor da corrente
         */
        void setPonto1(double x1, double y1)
        {
            ponto1.push_back(x1);
            ponto1.push_back(y1);
        }

        /**
         * Define os pontos x,y do ponto 2 no resistor
         * linear
         * @param x2 valor da tensao
         * @param y2 valor da corrente
         */
        void setPonto2(double x2, double y2)
        {
            ponto2.push_back(x2);
            ponto2.push_back(y2);
        }

        /**
         * Define os pontos x,y do ponto 3 no resistor
         * linear
         * @param x3 valor da tensao
         * @param y3 valor da corrente
         */
        void setPonto3(double x3, double y3)
        {
            ponto3.push_back(x3);
            ponto3.push_back(y3);
        }

        /**
         * Define os pontos x,y do ponto 4 no resistor
         * linear
         * @param x4 valor da tensao
         * @param y4 valor da corrente
         */
        void setPonto4(double x4, double y4)
        {
            ponto4.push_back(x4);
            ponto4.push_back(y4);
        }

        /**
         * Retorna o ponto 1
         */
        vector<double> getPonto1()
        {
            return ponto1;
        }

        /**
         * Retorna o ponto 2
         */
        vector<double> getPonto2()
        {
            return ponto2;
        }

        /**
         * Retorna o ponto 3
         */
        vector<double> getPonto3()
        {
            return ponto3;
        }

        /**
         * Retorna o ponto 4
         */
        vector<double> getPonto4()
        {
            return ponto4;
        }

        /**
         * Retorna a tensao no ponto pedido
         */
        double getTensaoNoPonto(vector<double> ponto)
        {
            return ponto[0];
        }

        /**
         * Retorna a corrente no ponto pedido
         */
        double getCorrenteNoPonto(vector<double> ponto)
        {
            return ponto[1];
        }

        /**
         * Pega a resistencia na primeira reta
         */
        double getDerivada1()
        {
            double deltaCorrente = getCorrenteNoPonto(getPonto2()) - getCorrenteNoPonto(getPonto1());
            double deltaTensao = getTensaoNoPonto(getPonto2()) - getTensaoNoPonto(getPonto1());
            return deltaCorrente / deltaTensao;
        }

        /**
         * Pega a resistencia na segunda reta
         */
        double getDerivada2()
        {
            double deltaCorrente = getCorrenteNoPonto(getPonto3()) - getCorrenteNoPonto(getPonto2());
            double deltaTensao = getTensaoNoPonto(getPonto3()) - getTensaoNoPonto(getPonto2());
            return deltaCorrente / deltaTensao;
        }

        /**
         * Pega a resistencia na terceira reta
         */
        double getDerivada3()
        {
            double deltaCorrente = getCorrenteNoPonto(getPonto4()) - getCorrenteNoPonto(getPonto3());
            double deltaTensao = getTensaoNoPonto(getPonto4()) - getTensaoNoPonto(getPonto3());
            return deltaCorrente / deltaTensao;
        }

        /**
         * Escolhe a reta de acordo com o ponto de operacao da tensao
         */
        double getInclinacao(double tensao)
        {
            if (tensao <= getTensaoNoPonto(getPonto2())) {
                return getDerivada1();
            } else if (tensao <= getTensaoNoPonto(getPonto3())) {
                return getDerivada2();
            }
            return getDerivada3();
        }

        /**
         * Pega a resistencia no ponte de operacao pedido
         */
        double getResistencia(double tensao)
        {
            return 1/getInclinacao(tensao);
        }

        /**
         * Corrente de acordo com a tensao no ponto de operacao
         */
        double getCorrente(double tensao)
        {
            if (tensao <= getTensaoNoPonto(getPonto2())) {
                return getCorrenteNoPonto(getPonto2()) - (
                    1/getResistencia(tensao) * getTensaoNoPonto(getPonto2())
                );
            } else if (tensao <= getTensaoNoPonto(getPonto3())) {
                return getCorrenteNoPonto(getPonto3()) - (
                    1/getResistencia(tensao) * getTensaoNoPonto(getPonto3())
                );
            }
                return getCorrenteNoPonto(getPonto4()) - (
                    1/getResistencia(tensao) * getTensaoNoPonto(getPonto4())
                );
        }

        /**
         * Estanpa da matriz nodal modificada para resistor nao linear
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


    private:
        /**
         * Ponto 1
         */
        vector<double> ponto1;

        /**
         * Ponto 2
         */
        vector<double> ponto2;

        /**
         * Ponto 3
         */
        vector<double> ponto3;

        /**
         * Ponto 4
         */
        vector<double> ponto4;
};

#endif