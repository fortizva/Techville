#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;
namespace util
{
    void mostrarMatriz(vector<vector<float>> matrix, vector<string> labels, int n)
    {
        // Mostrar etiquetas de columna
        cout << "      :";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << labels[i] << " ";
        }
        cout << endl;
        // Mostrar separador de línea
        cout << "······:";
        for (int i = 0; i < n * 6; i++)
        {

            cout << "·";
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            // Mostrar etiquetas de fila
            cout << setw(5) << labels[i] << " : ";
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == numeric_limits<float>::infinity())
                {
                    cout << " ***  ";
                }
                else
                {
                    cout << setw(5) << fixed << setprecision(2) << matrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    void mostrarMatriz(vector<vector<int>> matrix, vector<string> labels, int n)
    {
        // Mostrar etiquetas de columna
        cout << "      :";
        for (int i = 0; i < n; i++)
        {
            cout << setw(5) << labels[i] << " ";
        }
        cout << endl;
        // Mostrar separador de línea
        cout << "······:";
        for (int i = 0; i < n * 6; i++)
        {

            cout << "·";
        }
        cout << endl;

        for (int i = 0; i < n; i++)
        {
            // Mostrar etiquetas de fila
            cout << setw(5) << labels[i] << " : ";
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == numeric_limits<float>::infinity())
                {
                    cout << " ***  ";
                }
                else
                {
                    cout << setw(5) << matrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}
#endif