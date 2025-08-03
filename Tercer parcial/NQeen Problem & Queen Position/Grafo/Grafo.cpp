#include "Grafo.h"
#include <cmath>
#include <iostream>


#define M_PI 3.14159265358979323846


Grafo::Grafo() : numNodos(0), dirigido(true) {
    std::srand(std::time(0));
}

void Grafo::nuevoGrafo(int numNodos, bool dirigido) {
    this->numNodos = numNodos;
    this->dirigido = dirigido;
    matrizAdyacencia = std::vector<std::vector<int>>(numNodos, std::vector<int>(numNodos, 0));
    generarRelacionesAleatorias();
}

void Grafo::generarRelacionesAleatorias() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 5);

    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            if (i != j && dis(gen) == 0) {
                matrizAdyacencia[i][j] = 1;
                if (!dirigido) {
                    matrizAdyacencia[j][i] = 1;
                }
            }
        }
    }
}

void Grafo::representacionLogica() {
    std::cout << "\nRepresentacion Logica del Grafo:" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            if (matrizAdyacencia[i][j] == 1) {
                std::cout << i << " -> " << j << std::endl;
            }
        }
    }
}

void Grafo::representacionListaAdyacencia() {
    std::cout << "\nLista de Adyacencia:" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        std::cout << i << ": ";
        for (int j = 0; j < numNodos; ++j) {
            if (matrizAdyacencia[i][j] == 1) {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
    }
}

void Grafo::representacionMatrizAdyacencia() {
    std::cout << "\nMatriz de Adyacencia:" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            std::cout << matrizAdyacencia[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::busquedaAmplitud(int verticeInicial) {
    std::vector<bool> visitado(numNodos, false);
    std::queue<int> cola;
    
    cola.push(verticeInicial);
    visitado[verticeInicial] = true;
    
    std::cout << "\nRecorrido por Amplitud desde el vertice " << verticeInicial << ":" << std::endl;
    std::cout << "Vertice\tVisitado" << std::endl;
    
    while (!cola.empty()) {
        int vertice = cola.front();
        cola.pop();
        std::cout << vertice << "\ttrue" << std::endl;
        
        for (int i = 0; i < numNodos; ++i) {
            if (matrizAdyacencia[vertice][i] == 1 && !visitado[i]) {
                cola.push(i);
                visitado[i] = true;
            }
        }
    }
    
    for (int i = 0; i < numNodos; ++i) {
        if (!visitado[i]) {
            std::cout << i << "\tfalse" << std::endl;
        }
    }
}

void Grafo::mostrarRepresentacionGrafica(const std::string& tipo) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Grafo - " + tipo);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        if (tipo == "Logica") {
            dibujarGrafoLogico(window);
        } else if (tipo == "Lista") {
            dibujarListaAdyacencia(window);
        } else if (tipo == "Matriz") {
            dibujarMatrizAdyacencia(window);
        }

        window.display();
    }
}

void Grafo::dibujarFlecha(sf::RenderWindow& window, sf::Vector2f inicio, sf::Vector2f fin) {
    // Dibujar linea principal
    sf::RectangleShape linea(sf::Vector2f(
        std::sqrt(std::pow(fin.x - inicio.x, 2) + std::pow(fin.y - inicio.y, 2)), 2.f));
    linea.setPosition(inicio);
    float angulo = std::atan2(fin.y - inicio.y, fin.x - inicio.x) * 180 / M_PI;
    linea.setRotation(angulo);
    linea.setFillColor(sf::Color::Black);
    window.draw(linea);

    if (dirigido) {
        // Dibujar punta de flecha
        float arrowLength = 10.f;
        float arrowAngle = 30.f;
        
        sf::ConvexShape arrow;
        arrow.setPointCount(3);
        arrow.setFillColor(sf::Color::Black);
        
        float angle = std::atan2(fin.y - inicio.y, fin.x - inicio.x);
        arrow.setPoint(0, fin);
        arrow.setPoint(1, sf::Vector2f(
            fin.x - arrowLength * std::cos(angle - arrowAngle * M_PI / 180),
            fin.y - arrowLength * std::sin(angle - arrowAngle * M_PI / 180)));
        arrow.setPoint(2, sf::Vector2f(
            fin.x - arrowLength * std::cos(angle + arrowAngle * M_PI / 180),
            fin.y - arrowLength * std::sin(angle + arrowAngle * M_PI / 180)));
        
        window.draw(arrow);
    }
}

void Grafo::dibujarGrafoLogico(sf::RenderWindow& window) {
    const float radio = 20.f;
    std::vector<sf::Vector2f> posiciones(numNodos);
    
    // Calcular posiciones de los nodos en circulo
    float angulo = 2 * M_PI / numNodos;
    float radio_circulo = std::min(window.getSize().x, window.getSize().y) * 0.35f;
    sf::Vector2f centro(window.getSize().x / 2.f, window.getSize().y / 2.f);
    
    for (int i = 0; i < numNodos; ++i) {
        posiciones[i] = sf::Vector2f(
            centro.x + radio_circulo * std::cos(i * angulo),
            centro.y + radio_circulo * std::sin(i * angulo)
        );
    }

    // Dibujar aristas
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            if (matrizAdyacencia[i][j] == 1) {
                sf::Vector2f inicio = posiciones[i];
                sf::Vector2f fin = posiciones[j];
                
                // Ajustar puntos para que las flechas no crucen los nodos
                float angle = std::atan2(fin.y - inicio.y, fin.x - inicio.x);
                sf::Vector2f inicioAjustado(
                    inicio.x + radio * std::cos(angle),
                    inicio.y + radio * std::sin(angle)
                );
                sf::Vector2f finAjustado(
                    fin.x - radio * std::cos(angle),
                    fin.y - radio * std::sin(angle)
                );
                
                dibujarFlecha(window, inicioAjustado, finAjustado);
            }
        }
    }

    // Dibujar nodos
    for (int i = 0; i < numNodos; ++i) {
        sf::CircleShape nodo(radio);
        nodo.setFillColor(sf::Color::White);
        nodo.setOutlineThickness(2.f);
        nodo.setOutlineColor(sf::Color::Black);
        nodo.setPosition(posiciones[i].x - radio, posiciones[i].y - radio);
        window.draw(nodo);

        // Dibujar numero del nodo
        sf::Font font;
        if (font.loadFromFile("arial.ttf")) {
            sf::Text texto(std::to_string(i), font, 20);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(
                posiciones[i].x - texto.getGlobalBounds().width / 2,
                posiciones[i].y - texto.getGlobalBounds().height / 2
            );
            window.draw(texto);
        }
    }
}

void Grafo::dibujarListaAdyacencia(sf::RenderWindow& window) {
    const float cellHeight = 40.f;
    const float cellWidth = 40.f;
    const float startX = 50.f;
    const float startY = 50.f;
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;

    for (int i = 0; i < numNodos; ++i) {
        // Dibujar nodo principal
        sf::RectangleShape nodo(sf::Vector2f(cellWidth, cellHeight));
        nodo.setPosition(startX, startY + i * (cellHeight + 10));
        nodo.setFillColor(sf::Color::White);
        nodo.setOutlineColor(sf::Color::Black);
        nodo.setOutlineThickness(2.f);
        window.draw(nodo);

        // Numero del nodo
        sf::Text texto(std::to_string(i), font, 20);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(
            startX + cellWidth/2 - texto.getGlobalBounds().width/2,
            startY + i * (cellHeight + 10) + cellHeight/2 - texto.getGlobalBounds().height/2
        );
        window.draw(texto);

        // Dibujar lista de adyacencia
        float xOffset = startX + cellWidth + 20;
        for (int j = 0; j < numNodos; ++j) {
            if (matrizAdyacencia[i][j] == 1) {
                // Dibujar flecha de conexion
                sf::RectangleShape flecha(sf::Vector2f(20, 2));
                flecha.setPosition(xOffset - 20, startY + i * (cellHeight + 10) + cellHeight/2);
                flecha.setFillColor(sf::Color::Black);
                window.draw(flecha);

                // Dibujar nodo adyacente
                sf::RectangleShape nodoAdj(sf::Vector2f(cellWidth, cellHeight));
                nodoAdj.setPosition(xOffset, startY + i * (cellHeight + 10));
                nodoAdj.setFillColor(sf::Color::White);
                nodoAdj.setOutlineColor(sf::Color::Black);
                nodoAdj.setOutlineThickness(2.f);
                window.draw(nodoAdj);

                // Numero del nodo adyacente
                sf::Text textoAdj(std::to_string(j), font, 20);
                textoAdj.setFillColor(sf::Color::Black);
                textoAdj.setPosition(
                    xOffset + cellWidth/2 - textoAdj.getGlobalBounds().width/2,
                    startY + i * (cellHeight + 10) + cellHeight/2 - textoAdj.getGlobalBounds().height/2
                );
                window.draw(textoAdj);

                xOffset += cellWidth + 20;
            }
        }
    }
}

void Grafo::dibujarMatrizAdyacencia(sf::RenderWindow& window) {
    const float cellSize = 40.f;
    const float startX = 100.f;
    const float startY = 100.f;
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;

    // Dibujar numeros de columna
    for (int j = 0; j < numNodos; ++j) {
        sf::Text texto(std::to_string(j), font, 20);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(
            startX + j * cellSize + cellSize/2 - texto.getGlobalBounds().width/2,
            startY - cellSize
        );
        window.draw(texto);
    }

    // Dibujar numeros de fila
    for (int i = 0; i < numNodos; ++i) {
        sf::Text texto(std::to_string(i), font, 20);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(
            startX - cellSize,
            startY + i * cellSize + cellSize/2 - texto.getGlobalBounds().height/2
        );
        window.draw(texto);
    }

    // Dibujar matriz
    for (int i = 0; i < numNodos; ++i) {
        for (int j = 0; j < numNodos; ++j) {
            sf::RectangleShape celda(sf::Vector2f(cellSize, cellSize));
            celda.setPosition(startX + j * cellSize, startY + i * cellSize);
            celda.setFillColor(sf::Color::White);
            celda.setOutlineColor(sf::Color::Black);
            celda.setOutlineThickness(1.f);
            window.draw(celda);

            sf::Text valor(std::to_string(matrizAdyacencia[i][j]), font, 20);
            valor.setFillColor(sf::Color::Black);
            valor.setPosition(
                startX + j * cellSize + cellSize/2 - valor.getGlobalBounds().width/2,
                startY + i * cellSize + cellSize/2 - valor.getGlobalBounds().height/2
            );
            window.draw(valor);
        }
    }
}