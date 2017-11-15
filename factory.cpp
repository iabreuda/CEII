#ifndef FACTORY
#define FACTORY

/**
 * Modelo basico para componentes
 */
#include "components.cpp"
/**
 * Modelo basico componentes lineares
 */
#include "lineares.cpp"
/**
 * Modelo de resistor linear
 */
#include "resistor.cpp"
 /**
 * Modelo de capacitor linear
 */
#include "capacitor.cpp"
 /**
 * Modelo de resistor linear
 */
#include "indutor.cpp"

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Factory
{
    public:
        /**
         * Construtor
         */
        Factory(vector<vector<string> > listOfElements)
        {
            setup(listOfElements);
        }

    private:
        vector<Components> elementos;
        void setup(vector<vector<string> > listOfElements)
        {
            //iterates here
        }
};

#endif