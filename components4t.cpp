#ifndef COMPONENTS4T
#define COMPONENTS4T
/**
 * Modelo basico para componentes
 */
#include "components.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Components4t : public Components
{
    public:
        /**
         * Construtor
         */
        Components4t(string n, int a, int b, int c, int d) : Components(n, a, b)
        {
            setNoC(c);
            setNoD(d);
            setNos(4);
        }

        /**
         * Define o no C do componente
         * @param c no C
         */
        void setNoC(int c)
        {
            noC = c;
        }

        /**
         * Retorna o no C
         */
        int getNoC()
        {
            return noC;
        }

        /**
         * Define o no D do componente
         * @param b no D
         */
        void setNoD(int d)
        {
            noD = d;
        }

        /**
         * Retorna o no D
         */
        int getNoD()
        {
            return noD;
        }

        /**
         * Componente tem 4 terminais?
         * @return true
         */
        bool has4t()
        {
            return true;
        }

    private:
        /**
         * Terminal C
         */
        int noC;
        /**
         * Terminal D
         */
        int noD;
};

#endif