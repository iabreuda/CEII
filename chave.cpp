#ifndef CHAVE
#define CHAVE
/**
 * Modelo basico componentes de 4 terminais
 */
#include "components4t.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Chave : public Components4t
{

    public:
        /**
         * Construtor
         */
        Chave(string n, int a, int b, int c, int d, double on, double off, double r) : Components4t(n, a, b, c, d)
        {
            setGOn(on);
            setGOff(off);
            setRef(r);
        }

        /**
         * Define gON da chave
         * @param on valor de gON
         */
        void setGOn(double on)
        {
            gon = on;
        }

        /**
         * Define gOff da chave
         * @param off valor de gOff
         */
        void setGOff(double off)
        {
            goff = off;
        }

        /**
         * Define ref da chave
         * @param r valor de Referencia
         */
        void setRef(double r)
        {
            ref = r;
        }

        /**
         * Retorna gON da chave
         */
        double getGOn()
        {
            return gon;
        }

        /**
         * Retorna gOff da chave
         */
        double getGOff()
        {
            return goff;
        }

        /**
         * Retorna a tensao de referencia da chave
         */
        double getRef()
        {
            return ref;
        }

        /**
         * Retorna a resistencia da tensao de acordo com
         * o ponto de operacao definido pea tensao no ramo
         * no instante anterior
         */
        double getResistencia(double tensao)
        {
            if (tensao <= getRef()) {
                return 1/getGOff();
            }
            return 1/getGOn();
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
             * Pega a tensao no ramo no instante anterior
             */
            double tensaoRamo = resultado[getNoC()] - resultado[getNoD()];
            /**
             * Descarta o no Zero uma vez que ele e linearmente dependente
             */
            if (getNoC() == 0) {
                tensaoRamo = -1*resultado[getNoB()];
            }
            if (getNoD() == 0) {
                tensaoRamo = resultado[getNoA()];
            }

            condutancia[getNoA()][getNoA()] += 1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoB()] += 1/getResistencia(tensaoRamo);
            condutancia[getNoA()][getNoB()] += -1/getResistencia(tensaoRamo);
            condutancia[getNoB()][getNoA()] += -1/getResistencia(tensaoRamo);
        }


    private:
        /**
         * Condutancia quando a tensao entre o no C e D e
         * maior que a referencia
         */
        double gon;

        /**
         * Condutancia quando a tensao entre o no C e D e
         * menor ou igual a referencia
         */
        double goff;

        /**
         * Tensao de referencia
         */
        double ref;
};

#endif