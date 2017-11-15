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
        Components4t(string n, int a, int b, int c, int d) : Components(n, a, b)
        {
            setNome(n);
            setNoA(a);
            setNoB(b);
        }

        void setNoC(int c)
        {
            noC = c;
        }

        int getNoC()
        {
            return noC;
        }

        void setNoD(int d)
        {
            noD = d;
        }

        int getNoD()
        {
            return noD;
        }

    private:
        int noC;
        int noD;
};

#endif