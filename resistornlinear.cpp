#ifndef RESISTORNLINEAR
#define RESISTORNLINEAR
/**
 * Modelo basico de componentes
 */
#include "resistor.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class ResistorNLinear : public Resistor
{
    public:
        /**
         * Construtor
         */
        ResistorNLinear(string n, int a, int b, double v,
            double x1, double y1,
            double x2, double y2,
            double x3, double y3,
            double x4, double y4) : Resistor(n, a, b, v)
        {
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
            ponto1[0] = x1;
            ponto1[1] = y1;
        }

        /**
         * Define os pontos x,y do ponto 2 no resistor
         * linear
         * @param x2 valor da tensao
         * @param y2 valor da corrente
         */
        void setPonto2(double x2, double y2)
        {
            ponto1[0] = x2;
            ponto1[1] = y2;
        }

        /**
         * Define os pontos x,y do ponto 3 no resistor
         * linear
         * @param x3 valor da tensao
         * @param y3 valor da corrente
         */
        void setPonto3(double x3, double y3)
        {
            ponto1[0] = x3;
            ponto1[1] = y3;
        }

        /**
         * Define os pontos x,y do ponto 4 no resistor
         * linear
         * @param x4 valor da tensao
         * @param y4 valor da corrente
         */
        void setPonto4(double x4, double y4)
        {
            ponto1[0] = x4;
            ponto1[1] = y4;
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