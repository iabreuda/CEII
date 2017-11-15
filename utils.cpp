#ifndef UTILS
#define UTILS
/**
 * Inclui:
 *  - istringstream
 */
#include <sstream>

/* Necessario para nao precisar escrever std:: */
using namespace std;

/**
 * Transformar uma string em elementos de um array utilizando um caracter delimitador
 * Ex. explode("Hello World", ' ')
 * Retorna:
 *     vector[0] = "Hello"
 *     vector[1] = "World"
 */
const vector<string> explode(const string& phrase, char delim)
{
    vector<string> result;
    istringstream iss(phrase);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

#endif