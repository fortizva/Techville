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

    // Leer intersecciones priorizadas
    string header;
    cin >> header; // Leer "Prioridades"

    vector<tuple<string, string, int>> prioridades;

    string inter1, inter2;
    int prioridad;

    for(int i=0; i < m; i++)
    {
        cin >> inter1 >> inter2 >> prioridad;
        prioridades.push_back(make_tuple(inter1, inter2, prioridad));
    }

    // Calculamos las rutas más cortas usando el algoritmo de Floyd-Warshall
    g.Floyd();

    // Mostrar las rutas más cortas
    int i, j;
    for (int c = 0; c < consultas.size(); c++)
    {
        i = g.getIndex(consultas[c].first);
        j = g.getIndex(consultas[c].second);

        if (consultas[c].first != consultas[c].second)
        {
            g.mostrarRuta(i, j);
        }
    }

    cout << endl;

    // Calcular rutas más cortas usando intersecciones priorizadas
    Grafo gp = Grafo();

    // Agregar vértices
    for (int i = 0; i < n; ++i)
    {
        gp.addVertice(g.getVertices()[i]);
    }

    // Agregar aristas
    for (int i = 0; i < prioridades.size(); ++i)
    {
        gp.addArista(get<0>(prioridades[i]), get<1>(prioridades[i]), get<2>(prioridades[i]));
    }

    // Calcular arból de expansión mínima
    Grafo gres = Grafo();
    gp.Kruskal(gres);

    // Calcular suma de los pesos de las aristas
    float ca = 0;
    for (int i = 0; i < gres.getNumVertices(); i++)
    {
        for (int j = 0; j < gres.getNumVertices(); j++)
        {
            if (gres.getArista(i, j) < gres.getINF() && i < j)
            {
                ca += g.getArista(i, j);
            }
        }
    }
    cout << fixed << setprecision(1) << ca << endl << endl;

    gres.Floyd();


    // Mostrar las rutas más cortas usando las intersecciones priorizadas
    for (int c = 0; c < consultas.size(); c++)
    {
        i = gres.getIndex(consultas[c].first);
        j = gres.getIndex(consultas[c].second);

        if (consultas[c].first != consultas[c].second)
        {
            gres.mostrarRutaP(i, j, g);
        }
    }

    return 0;
}