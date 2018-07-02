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
         * Estanpa da matriz nodal modificada amp op
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         * @param nodes       matriz de nos
         */
        void estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado)
        {
        }
};

#endif