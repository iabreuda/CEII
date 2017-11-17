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
         * Define a resistencia do indutor
         * @param v valor da resistencia
         */
        void setResistencia(double v)
        {
            resistencia = v;
        }

        /**
         * Retorna a resistencia do indutor
         */
        double getResistencia()
        {
            return resistencia;
        }

        /**
         * Define a tensao no indutor
         * @param v valor da tensao
         */
        void setTensao(double v)
        {
            tensao = v;
        }

        /**
         * Retorna a tensao do indutor
         */
        double getTensao()
        {
            return tensao;
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

    private:
        /**
         * Resistencia associada ao modelo do indutor
         * no trapezio
         */
        double resistencia;
        /**
         * Tensao da fonte de tensao
         * associada ao modelo do indutor no trapezio
         */
        double tensao;
        /**
         * valor da indutancia do capacitor
         */
        double indutancia;
};

#endif