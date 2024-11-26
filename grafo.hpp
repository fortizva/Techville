#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

class Grafo
{
private:
    const float INF = 999999;
    int numVertices;
    vector<string> vertices;
    vector<vector<float>> aristas;
    vector<vector<float>> adjMatrix;
    vector<vector<float>> cMatrix;
    vector<vector<int>> pMatrix;

    float mostrarRuta(int i, int j, float acum)
    {
        int k = pMatrix[i][j];
        if (k != -1)
        {
            acum = mostrarRuta(i, k, acum);
            cout << " " << vertices[k];
            acum = mostrarRuta(k, j, acum);
        }
        else
        {
            acum += getArista(i, j);
        }
        return acum;
    }

    float mostrarRutaP(int i, int j, float acum, Grafo g)
    {
        int k = pMatrix[i][j];
        if (k != -1)
        {
            acum = mostrarRutaP(i, k, acum, g);
            cout << " " << vertices[k];
            acum = mostrarRutaP(k, j, acum, g);
        }
        else
        {
            acum += g.getArista(i, j);
        }
        return acum;
    }

    bool generaCiclosUtil(int i, int j, vector<bool>& visited) 
    {
        if (i == j) return true;
        visited[i] = true;
        for (int k = 0; k < numVertices; k++) // Explorar vecinos
        {
            if (aristas[i][k] < INF && !visited[k]) // Si hay arista y no ha sido visitado
            {
                if (k==j || generaCiclosUtil(k, j, visited)) return true;
            }
        }
        return false;
    }

public:
    Grafo()
    {
        numVertices = 0;
        vertices = vector<string>();
        aristas = vector<vector<float>>();
        adjMatrix = vector<vector<float>>();
        vector<vector<float>> cMatrix = vector<vector<float>>();
        vector<vector<int>> pMatrix(numVertices, vector<int>(numVertices, -1));
    }

    void addVertice(string vertice)
    {
        // Agregamos el vértice a la lista
        vertices.push_back(vertice);

        // Agregamos una columna a cada fila de aristas
        for (int i = 0; i < numVertices; i++)
        {
            aristas[i].push_back(INF);
        }
        // Añadimos la fila de este vértice
        numVertices++;
        aristas.push_back(vector<float>(numVertices, INF));
        // Agregamos un 0 en la fila y columna del vértice
        aristas[numVertices - 1][numVertices - 1] = 0;
    }

    void addArista(string vertice1, string vertice2, float peso)
    {
        int i = -1;
        int j = -1;
        // Encontrar vértices en la lista
        for (int k = 0; k < numVertices; k++)
        {
            if (vertices[k] == vertice1)
            {
                i = k;
            }
            if (vertices[k] == vertice2)
            {
                j = k;
            }
        }
        if (i == -1 || j == -1)
        {
            cout << "ERROR: No se encontraron los vértices para la inserción de la arista:" << endl;
            cout << "\t" << vertice1 << " <-> " << vertice2 << endl;
            return;
        }
        else
        {
            aristas[i][j] = peso;
            aristas[j][i] = peso;
            
        }
    }

    void mostrarVertices()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << vertices[i] << " ";
        }
        cout << endl;
    }

    void mostrarAristas()
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (aristas[i][j] < INF && i!=j) // Comparar igualdad con el float puede dar errores
                {
                    cout << vertices[i] << " <-> " << vertices[j] << " : " << aristas[i][j] << endl;
                }
            }
        }
    }

    void mostrarMatrizAdj()
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (adjMatrix[i][j] >= INF) // Comparar igualdad con float puede dar errores
                {
                    cout << "0 ";
                }
                else
                {
                    cout << adjMatrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    void mostrarMatrizC()
    {
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (cMatrix[i][j] >= INF) // Comparar igualdad con float puede dar errores
                {
                    cout << "0 ";
                }
                else
                {
                    cout << cMatrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }
    

    // Retorna duplicado de la matriz de adyacencia
    vector<vector<float>> getAdjMatrix()
    {
        vector<vector<float>> adjMatrixCopy = vector<vector<float>>(numVertices, vector<float>(numVertices, INF+1.0f)); // Usamos INF+1 para evitar errores de comparación
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                adjMatrixCopy[i][j] = adjMatrix[i][j];
            }
        }
        return adjMatrixCopy;
    }

    vector<string> getVertices()
    {
        return vertices;
    }

    // Devuelve el índice de un vértice en la lista de vértices
    int getIndex(string vertice)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (vertices[i] == vertice)
            {
                return i;
            }
        }
        return -1;
    }

    int getNumVertices()
    {
        return numVertices;
    }

    float getAristaAdj(int i, int j)
    {
        return adjMatrix[i][j];
    }

    float getArista(int i, int j)
    {
        return aristas[i][j];
    }

    float getCosto(int i, int j)
    {
        return cMatrix[i][j];
    }

    // Algoritmo de Floyd-Warshall
    void Floyd()
    {
        int i, j, k;
        // Preparamos las matrices
        // Copiamos contenido de la matriz aristas a adjMatrix

        adjMatrix = vector<vector<float>>(numVertices, vector<float>(numVertices, INF+1.0f)); // Usamos INF+1 para evitar errores de comparación
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                adjMatrix[i][j] = aristas[i][j];
            }
        }

        // Inicializamos la matriz de costos
        cMatrix = vector<vector<float>>(numVertices, vector<float>(numVertices, INF+1.0f)); // Usamos INF+1 para evitar errores de comparación
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (adjMatrix[i][j] < INF) // Comparar igualdad con float puede dar errores, por lo que usamos menor que
                {
                    cMatrix[i][j] = adjMatrix[i][j];
                }
            }
        }

        // Inicializamos la matriz de caminos
        pMatrix = vector<vector<int>>(numVertices, vector<int>(numVertices, -1));

        for (k = 0; k < numVertices; k++)
        {
            for (i = 0; i < numVertices; i++)
            {
                for (j = 0; j < numVertices; j++)
                {
                    if (cMatrix[i][k] + cMatrix[k][j] < cMatrix[i][j])
                    {
                        cMatrix[i][j] = cMatrix[i][k] + cMatrix[k][j];
                        pMatrix[i][j] = k;
                    }
                }
            }
        }
    }

    float mostrarRuta(int i, int j)
    {
        float acum = 0;
        cout << vertices[i];
        acum = mostrarRuta(i, j, acum);
        cout << " " << vertices[j] << " " << fixed << setprecision(1) <<  acum << endl;
        return acum;
    }

    // Muestra la ruta más corta entre dos vértices usando las vías prioritarias, emplea otro grafo del que extraer las distancias
    float mostrarRutaP(int i, int j, Grafo g)
    {
        float acum = 0;
        cout << vertices[i];
        acum = mostrarRutaP(i, j, acum, g);
        cout << " " << vertices[j] << " " << fixed << setprecision(1) << acum << endl;
        return acum;
    }

    // Cálculo del costo acumulado de un grafo usando las vías prioritarias
    float getCostoAcumP(Grafo g)
    {
        float acum = 0;
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (cMatrix[i][j] < INF) // Comparar igualdad con float puede dar errores, por lo que usamos menor que
                {
                    acum += g.getCosto(i, j);
                }
            }
        }
        return acum;
    }

    float getINF()
    {
        return INF;
    }

    bool estanConectados(string vertice1, string vertice2)
    {
        int i = getIndex(vertice1);
        int j = getIndex(vertice2);
        return (i != -1 && j != -1 && aristas[i][j] < INF);
    }

    // Kruskal
    void Kruskal(Grafo &gres){
        // CjtoVertices
        vector<vector<string>> CjtoVertices;
        // u, v vertices
        vector<string> u, v;
        // a arista actual
        tuple<string, string, float> a;
        // x etiqueta
        string x;
        // Lista de aristas ordenada
        vector<tuple<string, string, float>> aristasOrdenadas;
        
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < i; j++) // j < i para no repetir aristas
            {
                if (aristas[i][j] < INF)
                {
                    aristasOrdenadas.push_back(make_tuple(vertices[i], vertices[j], aristas[i][j]));
                }
            }
        }

        sort(aristasOrdenadas.begin(), aristasOrdenadas.end(), [](const tuple<string, string, float> &a, const tuple<string, string, float> &b) {
            return get<2>(a) < get<2>(b);
        });


        // Inicializar gres
        for (int i = 0; i < numVertices; i++)
        {
            gres.addVertice(vertices[i]);
        }

        // mientras gres no sea conexo: seleccionar arista a mínima no examinada. Si a no provoca ciclos entonces se añade a gres
        // Iterar sobre las aristas ordenadas
        for (const tuple<string, string, float> &a : aristasOrdenadas) {
            string u = get<0>(a);
            string v = get<1>(a);
            float peso = get<2>(a);

            // Si no genera ciclo, añadir la arista al grafo resultante
            if (!gres.generaCiclos(u, v)) {
                gres.addArista(u, v, peso);
            }
        }
    

    }

    bool generaCiclos(string vertice1, string vertice2)
    {
        int i = getIndex(vertice1);
        int j = getIndex(vertice2);
        vector<bool> visited(numVertices, false);
        return generaCiclosUtil(i, j, visited);
    }

};

#endif // GRAFO_HPP