#include <iostream>
#include "grafo.hpp"
#include <string>
#include <fstream>

using namespace std;

int main()
{
    // Crear el grafo
    Grafo g = Grafo();

    // Obtener intersecciones
    int n;
    string interseccion;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        cin >> interseccion;
        g.addVertice(interseccion);
    }

    // Obtener carreteras
    int m;

    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        string inter1, inter2;
        double tiempo;
        cin >> inter1 >> inter2 >> tiempo;
        g.addArista(inter1, inter2, tiempo);
    }

    // Obtener consultas
    int p;
    vector<pair<string, string>> consultas;

    cin >> p;

    for (int i = 0; i < p; ++i)
    {
        string inter1, inter2;
        cin >> inter1 >> inter2;
        consultas.push_back({inter1, inter2});
    }

    // Mostrar la matriz de adyacencia
    g.mostrarMatrizAdj();

    // Calculamos las rutas más cortas usando el algoritmo de Floyd-Warshall
    g.Floyd();

    g.mostrarMatrizC();

    // En esta entrega no es necesario mostrar las rutas más cortas
    /*
    cout << "Rutas más cortas:" << endl;
    int i, j;
    for (int c = 0; c < consultas.size(); c++)
    {
        i = g.getIndex(consultas[i].first);
        j = g.getIndex(consultas[i].second);

        cout << "Ruta más corta de " << consultas[c].first << " a " << consultas[c].second << ":" << endl;
        cout << consultas[i].first;
        if (consultas[i].first != consultas[i].second)
        {
            g.mostrarRuta(i, j);
        }
        cout << " -> " << g.getVertices()[j] << endl;
        cout << endl;
    }
    */
    return 0;
}