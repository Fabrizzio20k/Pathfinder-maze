#pragma once
#include "maze.h"

#define SCREENWIDTH 1300
#define SCREENHEIGHT 600

enum GameScreen
{
    WELCOME,
    PLAYGROUND
};

auto maze1 = new Maze(20, 20);
auto maze2 = new Maze(20, 20);

// Main window options
const float columnWidth = static_cast<float>(SCREENWIDTH) / 7.5f;
const float gridMargin = 20.0f;                                // Margen entre el grid y la columna de opciones
const float gridPadding = 10.0f;                               // Espacio de separación entre el grid y los bordes de la ventana
const float gridSeparatorWidth = 25.0f;                        // Ancho de la línea de separación entre los grids
const float gridPosX = columnWidth + gridMargin + gridPadding; // Posición X del primer grid

// Maze options
float gridSize = 20.0f;
float m_size = 20.0f;
const float minGridSize = 20.0f;
const float maxGridSize = 50.0f;

// Variables para el porcentaje de obstáculos
float obstaclePercentage = 0.2f;
float percentage = 0.2f;
const float minObstaclePercentage = 0.1f;
const float maxObstaclePercentage = 0.4f;
const float obstaclePercentageStep = 0.05f;

const char *marker1 = " ";
const char *marker2 = " ";
const char *marker3 = " ";
const char *marker4 = " ";
const char *marker5 = " ";

bool saved = false;
bool runned = false;
bool deleted = false;
bool created = false;

bool con_obstaculos = false;
bool con_visitados = false;

int startCellX = -1;
int startCellY = -1;
int endCellX = -1;
int endCellY = -1;

int AlgFontSize = 20;
float AlgButtonWidth = 20;
float AlgButtonHeight = static_cast<float>(AlgFontSize);

long long time1 = 0;
long long time2 = 0;

vector<string> algorithms;

void algorithmButtons(float &AlgTextPosX, float &AlgTextPosY)
{
    // Dibujar el texto de Alg1
    const char *Alg1Text = "Dijsktra";
    DrawText(Alg1Text, AlgTextPosX - 15, AlgTextPosY + 60, AlgFontSize, BLACK);

    // Dibujar el botón de Alg1
    Rectangle Alg1Button = {AlgTextPosX - 50, AlgTextPosY + 60, AlgButtonWidth, AlgButtonHeight};
    DrawRectangleRec(Alg1Button, Fade(RED, 0.8f));
    DrawText(marker1, static_cast<int>(Alg1Button.x + Alg1Button.width / 2 - MeasureText("-", AlgFontSize) / 2),
             static_cast<int>(Alg1Button.y + Alg1Button.height / 2 - AlgFontSize / 2), AlgFontSize, BLACK);

    // Detectar interacción con el botón de Alg1
    if (marker1 == " " && algorithms.size() != 2)
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg1Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker1 = "*";
            algorithms.emplace_back(Alg1Text);
        }
    }
    else if (marker1 == "*")
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg1Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker1 = " ";
            algorithms.erase(remove(algorithms.begin(), algorithms.end(), Alg1Text), algorithms.end());
        }
    }

    // Dibujar el texto de Alg1
    const char *Alg2Text = "A* Eu";
    DrawText(Alg2Text, AlgTextPosX - 15, AlgTextPosY + 60 + AlgButtonHeight + 10, AlgFontSize, BLACK);

    // Dibujar el botón de Alg1
    Rectangle Alg2Button = {AlgTextPosX - 50, AlgTextPosY + 60 + AlgButtonHeight + 10, AlgButtonWidth, AlgButtonHeight};
    DrawRectangleRec(Alg2Button, Fade(RED, 0.8f));
    DrawText(marker2, static_cast<int>(Alg2Button.x + Alg2Button.width / 2 - MeasureText("-", AlgFontSize) / 2),
             static_cast<int>(Alg2Button.y + Alg2Button.height / 2 - AlgFontSize / 2), AlgFontSize, BLACK);

    // Detectar interacción con el botón de Alg1
    if (marker2 == " " && algorithms.size() != 2)
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg2Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker2 = "*";
            algorithms.emplace_back(Alg2Text);
        }
    }
    else if (marker2 == "*")
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg2Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker2 = " ";
            algorithms.erase(remove(algorithms.begin(), algorithms.end(), Alg2Text), algorithms.end());
        }
    }

    // Dibujar el texto de Alg3
    const char *Alg3Text = "A* Mh";
    DrawText(Alg3Text, AlgTextPosX - 15, AlgTextPosY + 60 + 2 * (AlgButtonHeight + 10), AlgFontSize, BLACK);

    // Dibujar el botón de Alg3
    Rectangle Alg3Button = {AlgTextPosX - 50, AlgTextPosY + 60 + 2 * (AlgButtonHeight + 10), AlgButtonWidth, AlgButtonHeight};
    DrawRectangleRec(Alg3Button, Fade(RED, 0.8f));
    DrawText(marker3, static_cast<int>(Alg3Button.x + Alg3Button.width / 2 - MeasureText("-", AlgFontSize) / 2),
             static_cast<int>(Alg3Button.y + Alg3Button.height / 2 - AlgFontSize / 2), AlgFontSize, BLACK);

    // Detectar interacción con el botón de Alg3
    if (marker3 == " " && algorithms.size() != 2)
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg3Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker3 = "*";
            algorithms.emplace_back(Alg3Text);
        }
    }
    else if (marker3 == "*")
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg3Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker3 = " ";
            algorithms.erase(remove(algorithms.begin(), algorithms.end(), Alg3Text), algorithms.end());
        }
    }

    // Dibujar el texto de Alg4
    const char *Alg4Text = "G-BFS Eu";
    DrawText(Alg4Text, AlgTextPosX - 15, AlgTextPosY + 60 + 3 * (AlgButtonHeight + 10), AlgFontSize, BLACK);

    // Dibujar el botón de Alg4
    Rectangle Alg4Button = {AlgTextPosX - 50, AlgTextPosY + 60 + 3 * (AlgButtonHeight + 10), AlgButtonWidth, AlgButtonHeight};
    DrawRectangleRec(Alg4Button, Fade(RED, 0.8f));
    DrawText(marker4, static_cast<int>(Alg4Button.x + Alg4Button.width / 2 - MeasureText("-", AlgFontSize) / 2),
             static_cast<int>(Alg4Button.y + Alg4Button.height / 2 - AlgFontSize / 2), AlgFontSize, BLACK);

    // Detectar interacción con el botón de Alg4
    if (marker4 == " " && algorithms.size() != 2)
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg4Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker4 = "*";
            algorithms.emplace_back(Alg4Text);
        }
    }
    else if (marker4 == "*")
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg4Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker4 = " ";
            algorithms.erase(remove(algorithms.begin(), algorithms.end(), Alg4Text), algorithms.end());
        }
    }

    // Dibujar el texto de Alg5
    const char *Alg5Text = "G-BFS Mh";
    DrawText(Alg5Text, AlgTextPosX - 15, AlgTextPosY + 60 + 4 * (AlgButtonHeight + 10), AlgFontSize, BLACK);
    // Dibujar el botón de Alg5
    Rectangle Alg5Button = {AlgTextPosX - 50, AlgTextPosY + 60 + 4 * (AlgButtonHeight + 10), AlgButtonWidth, AlgButtonHeight};
    DrawRectangleRec(Alg5Button, Fade(RED, 0.8f));
    DrawText(marker5, static_cast<int>(Alg5Button.x + Alg5Button.width / 2 - MeasureText("-", AlgFontSize) / 2),
             static_cast<int>(Alg5Button.y + Alg5Button.height / 2 - AlgFontSize / 2), AlgFontSize, BLACK);

    // Detectar interacción con el botón de Alg5
    if (marker5 == " " && algorithms.size() != 2)
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg5Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker5 = "*";
            algorithms.emplace_back(Alg5Text);
        }
    }
    else if (marker5 == "*")
    {
        if (CheckCollisionPointRec(GetMousePosition(), Alg5Button) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            marker5 = " ";
            algorithms.erase(remove(algorithms.begin(), algorithms.end(), Alg5Text), algorithms.end());
        }
    }
}

void drawGrids(Rectangle &optionsColumn)
{
    // Calcular el tamaño del cuadrado del grid considerando el espacio de separación
    float gridSquareSize =
        (SCREENWIDTH - columnWidth - gridMargin * 2 - gridPadding * 2 - gridSeparatorWidth) / 2.0f;
    float cellSize = gridSquareSize / gridSize;

    // Calcular la posición del primer grid
    Vector2 gridPos = {columnWidth + gridMargin + gridPadding, (SCREENHEIGHT - gridSquareSize) * 0.5f};

    if (saved == true && algorithms.size() > 0)
    {
        const char *g1Text = algorithms[0].c_str();
        const char *g1Time = (to_string(time1) + " microseconds").c_str();

        int g1FontSize = 22;
        float g1TextPosX = optionsColumn.x + 450;
        float g1TextPosY = 10;
        DrawText(g1Text, g1TextPosX, g1TextPosY, g1FontSize, BLACK);

        if(runned)
            DrawText(g1Time, g1TextPosX, g1TextPosY + 560, g1FontSize, BLACK);
    }

    if (saved == true && algorithms.size() > 1)
    {
        const char *g2Text = algorithms[1].c_str();
        const char *g2Time = (to_string(time2) + " microseconds").c_str();

        int g2FontSize = 22;
        float g2TextPosX = optionsColumn.x + 1000;
        float g2TextPosY = 10;
        DrawText(g2Text, g2TextPosX, g2TextPosY, g2FontSize, BLACK);

        if(runned)
            DrawText(g2Time, g2TextPosX, g2TextPosY + 560, g2FontSize, BLACK);
    }

    vector<vector<Node>> grid = maze1->getNodes();
    vector<vector<Node>> grid2 = maze2->getNodes();

    // Verificar si se hizo clic en una celda del grid
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, Rectangle{gridPos.x, gridPos.y, gridSquareSize, gridSquareSize}))
        {
            int cellX = static_cast<int>((mousePos.x - gridPos.x) / cellSize);
            int cellY = static_cast<int>((mousePos.y - gridPos.y) / cellSize);

            if (!con_obstaculos || !grid[cellX][cellY].isBlocked)
            {
                if (startCellX == -1 && startCellY == -1)
                {
                    startCellX = cellX;
                    startCellY = cellY;
                }
                else if (endCellX == -1 && endCellY == -1)
                {
                    endCellX = cellX;
                    endCellY = cellY;
                }
            }
        }
    }

    // Dibujar el primer grid
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            Rectangle cellRect = {gridPos.x + static_cast<float>(i) * cellSize,
                                  gridPos.y + static_cast<float>(j) * cellSize, cellSize, cellSize};
            DrawRectangleRec(cellRect, WHITE);
            DrawRectangleLinesEx(cellRect, 1, Fade(GRAY, 0.5f));

            if (con_obstaculos)
            {
                if (grid[i][j].isBlocked)
                {
                    DrawRectangleRec(cellRect, BLACK);
                }
            }

            if (con_visitados)
            {
                if (grid[i][j].isVisited)
                {
                    DrawRectangleRec(cellRect, BLUE);
                }
            }

            if (runned)
            {
                for (auto c : maze1->reconstructPath())
                {
                    if (c->x == i && c->y == j)
                        DrawRectangleRec(cellRect, ORANGE);
                }
            }

            if (i == startCellX && j == startCellY)
                DrawRectangleRec(cellRect, GREEN);

            if (i == endCellX && j == endCellY)
                DrawRectangleRec(cellRect, RED);
        }
    }

    // Calcular la posición del segundo grid
    gridPos.x += gridSquareSize + gridSeparatorWidth;

    // Dibujar el segundo grid
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            Rectangle cellRect = {gridPos.x + static_cast<float>(i) * cellSize, gridPos.y + static_cast<float>(j) * cellSize, cellSize, cellSize};
            DrawRectangleRec(cellRect, WHITE);
            DrawRectangleLinesEx(cellRect, 1, Fade(GRAY, 0.5f));

            if (con_obstaculos)
            {
                if (grid2[i][j].isBlocked)
                {
                    DrawRectangleRec(cellRect, BLACK);
                }
            }

            if (con_visitados)
            {
                if (grid2[i][j].isVisited)
                {
                    DrawRectangleRec(cellRect, BLUE);
                }
            }
            if (runned)
            {
                for (auto c : maze2->reconstructPath())
                {
                    if (c->x == i && c->y == j)
                        DrawRectangleRec(cellRect, ORANGE);
                }
            }

            if (i == startCellX && j == startCellY)
                DrawRectangleRec(cellRect, GREEN);

            if (i == endCellX && j == endCellY)
                DrawRectangleRec(cellRect, RED);
        }
    }
}