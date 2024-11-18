#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

class Grafo
{
private:
    int numVertices;
    vector<string> vertices;
    vector<vector<float>> adjMatrix;
    vector<vector<float>> cMatrix;
    vector<vector<int>> pMatrix;

public:
    Grafo()
    {
        numVertices = 0;
        vertices = vector<string>();
        adjMatrix = vector<vector<float>>();
        vector<vector<float>> cMatrix = vector<vector<float>>();
        vector<vector<int>> pMatrix(numVertices, vector<int>(numVertices, -1));
    }

    void addVertice(string vertice)
    {
        // Agregamos el vértice a la lista
        vertices.push_back(vertice);

        // Agregamos una columna a cada fila de adjMatrix
        for (int i = 0; i < numVertices; i++)
        {
            adjMatrix[i].push_back(numeric_limits<float>::infinity());
        }
        // Añadimos la fila de este vértice
        numVertices++;
        adjMatrix.push_back(vector<float>(numVertices, numeric_limits<float>::infinity()));
        // Agregamos un 0 en la fila y columna del vértice
        adjMatrix[numVertices - 1][numVertices - 1] = 0;
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
            adjMatrix[i][j] = peso;
            adjMatrix[j][i] = peso;
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
                if (adjMatrix[i][j] != numeric_limits<float>::infinity())
                {
                    cout << vertices[i] << " <-> " << vertices[j] << " : " << adjMatrix[i][j] << endl;
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
                if (adjMatrix[i][j] == numeric_limits<float>::infinity())
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
                if (cMatrix[i][j] == numeric_limits<float>::infinity())
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
        vector<vector<float>> adjMatrixCopy = vector<vector<float>>(numVertices, vector<float>(numVertices, numeric_limits<float>::infinity()));
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

    // Algoritmo de Floyd-Warshall
    void Floyd()
    {
        int i, j, k;
        // Preparamos las matrices
        cMatrix = getAdjMatrix();
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

    void mostrarRuta(int i, int j)
    {
        int k = pMatrix[i][j];
        if (k != -1)
        {
            mostrarRuta(i, k);
            cout << " -> " << vertices[k];
            mostrarRuta(k, j);
        }
    }
};

#endif // GRAFO_HPP