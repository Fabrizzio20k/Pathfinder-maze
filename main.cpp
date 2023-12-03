#include "maze.h"
#include "raylib.h"
#include "variables.h"

int main()
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "The best path finder");
    SetTargetFPS(60);

    GameScreen currentScreen = WELCOME;

    Image icon = LoadImage(ASSETS_PATH "logo.png");
    // Crear y dibujar el logo de la ventana
    Image logo = LoadImage(ASSETS_PATH "logo.png");

    int logoWidth = logo.width / 4;
    int logoHeight = logo.height / 4;
    int logoPosX = SCREENWIDTH / 2 - logoWidth / 2;
    int logoPosY = SCREENHEIGHT / 2 - logoHeight / 2 + 150;

    ImageResize(&logo, logoWidth, logoHeight);
    Texture2D logoTexture = LoadTextureFromImage(logo);

    SetWindowIcon(icon);

    while (!WindowShouldClose())
    {
        if (currentScreen == WELCOME)
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentScreen = PLAYGROUND;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Mostrar la pantalla de bienvenida
            const char *title = "The best path finder";
            const char *subtitle = "Click to start!!!";
            int titleFontSize = 40;
            int subtitleFontSize = 20;
            int titleWidth = MeasureText(title, titleFontSize);
            int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

            // Calcular la posición del título y subtítulo en la ventana
            int titlePosX = SCREENWIDTH / 2 - titleWidth / 2;
            int titlePosY = SCREENHEIGHT / 2 - titleFontSize;
            int subtitlePosX = SCREENWIDTH / 2 - subtitleWidth / 2;
            int subtitlePosY = titlePosY + titleFontSize + 10; // Separación de 10 píxeles

            // Dibujar el título y subtítulo en la ventana
            DrawText(title, titlePosX, titlePosY, titleFontSize, BLACK);
            DrawText(subtitle, subtitlePosX, subtitlePosY, subtitleFontSize, GRAY);

            DrawTexture(logoTexture, logoPosX, logoPosY, WHITE);

            EndDrawing();
        }
        else
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            Rectangle optionsColumn = {0.0f, 0.0f, columnWidth, static_cast<float>(SCREENHEIGHT)};
            DrawRectangleRec(optionsColumn, Fade(LIGHTGRAY, 0.8f));

            // Mostrar el texto "Options"
            const char *optionsText = "OPTIONS";
            int optionsFontSize = 24;
            int optionsTextWidth = MeasureText(optionsText, optionsFontSize);
            int optionsTextPosX = optionsColumn.x + optionsColumn.width / 2 - optionsTextWidth / 2;
            int optionsTextPosY = 60;
            DrawText(optionsText, optionsTextPosX, optionsTextPosY, optionsFontSize, BLACK);

            // Mostrar el texto "Size"

            char *sizeText = "Size";
            int sizeFontSize = 24;
            int sizeTextWidth = MeasureText(sizeText, sizeFontSize);
            int sizeTextPosX = optionsColumn.x + optionsColumn.width / 2 - sizeTextWidth / 2;
            int sizeTextPosY = optionsTextPosY + optionsFontSize + 10;

            if (!created)
                DrawText(sizeText, sizeTextPosX, sizeTextPosY, sizeFontSize, BLACK);
            else
            {
                sizeText = ">> Maze <<";
                DrawText(sizeText, sizeTextPosX / 2, sizeTextPosY, sizeFontSize, GRAY);
            }

            // Mostrar el tamaño actual del grid
            char gridSizeText[10];
            sprintf(gridSizeText, "%.0f x %.0f", m_size, m_size);
            int optionFontSize = 24;
            int gridSizeTextWidth = MeasureText(gridSizeText, optionFontSize);
            float gridSizeTextPosX = columnWidth / 2.0f - static_cast<float>(gridSizeTextWidth) / 2.0f;
            float gridSizeTextPosY = sizeTextPosY + sizeFontSize + 10.0f;

            if (!created)
                DrawText(gridSizeText, static_cast<int>(gridSizeTextPosX), static_cast<int>(gridSizeTextPosY), optionFontSize, BLACK);
            else
            {
                sprintf(gridSizeText, "%.0f x %.0f", gridSize, gridSize);
                DrawText(gridSizeText, static_cast<int>(gridSizeTextPosX), static_cast<int>(gridSizeTextPosY), optionFontSize, GRAY);
            }
            // Dibujar el botón "-" para reducir el tamaño del grid
            if (!created)
            {
                Rectangle minusButton = {gridSizeTextPosX, gridSizeTextPosY + optionFontSize + 10.0f,
                                         gridSizeTextWidth / 2.0f - 5.0f, optionFontSize + 10.0f};
                if (m_size > minGridSize)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), minusButton) &&
                        IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        m_size -= 10.0f;
                        if (m_size < minGridSize)
                        {
                            m_size = minGridSize;
                        }
                    }
                }
                DrawRectangleRec(minusButton, Fade(SKYBLUE, 0.8f));
                DrawText("-",
                         static_cast<int>(minusButton.x + minusButton.width / 2 - MeasureText("-", optionFontSize) / 2),
                         static_cast<int>(minusButton.y + minusButton.height / 2 - optionFontSize / 2), optionFontSize,
                         BLACK);

                // Dibujar el botón "+" para aumentar el tamaño del grid
                Rectangle plusButton = {gridSizeTextPosX + gridSizeTextWidth / 2.0f + 5.0f,
                                        gridSizeTextPosY + optionFontSize + 10.0f, gridSizeTextWidth / 2.0f - 5.0f,
                                        optionFontSize + 10.0f};
                if (m_size < maxGridSize)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), plusButton) &&
                        IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        m_size += 10.0f;
                        if (m_size > maxGridSize)
                        {
                            m_size = maxGridSize;
                        }
                    }
                }

                DrawRectangleRec(plusButton, Fade(SKYBLUE, 0.8f));
                DrawText("+", static_cast<int>(plusButton.x + plusButton.width / 2 - MeasureText("+", optionFontSize) / 2),
                         static_cast<int>(plusButton.y + plusButton.height / 2 - optionFontSize / 2), optionFontSize,
                         BLACK);
            }

            // Mostrar el texto "Obstacles"
            const char *obstacleText = "Obstacles";
            int obstacleFontSize = 24;
            int obstacleTextWidth = MeasureText(obstacleText, obstacleFontSize);
            int obstacleTextPosX = optionsColumn.x + optionsColumn.width / 2 - obstacleTextWidth / 2;
            int obstacleTextPosY = sizeTextPosY + sizeFontSize + 100; // Espaciado adicional
            DrawText(obstacleText, obstacleTextPosX, obstacleTextPosY, obstacleFontSize, BLACK);

            // Mostrar el porcentaje de obstáculos actual
            char obstaclePercentageText[10];
            sprintf(obstaclePercentageText, "%.0f%%", percentage * 100);
            int obstaclePercentageFontSize = 24;
            int obstaclePercentageTextWidth = MeasureText(obstaclePercentageText, obstaclePercentageFontSize);
            int obstaclePercentageTextPosX =
                optionsColumn.x + optionsColumn.width / 2 - obstaclePercentageTextWidth / 2;
            int obstaclePercentageTextPosY = obstacleTextPosY + obstacleFontSize + 10;
            DrawText(obstaclePercentageText, obstaclePercentageTextPosX, obstaclePercentageTextPosY,
                     obstaclePercentageFontSize, BLACK);

            // Dibujar el botón "-" para reducir el porcentaje de obstáculos
            Rectangle minusObstacleButton = {gridSizeTextPosX,
                                             obstaclePercentageTextPosY + obstaclePercentageFontSize + 10.0f,
                                             gridSizeTextWidth / 2.0f - 5.0f, obstaclePercentageFontSize + 10.0f};
            if (percentage > minObstaclePercentage)
            {
                if (CheckCollisionPointRec(GetMousePosition(), minusObstacleButton) &&
                    IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    percentage -= obstaclePercentageStep;
                    if (percentage < minObstaclePercentage)
                    {
                        percentage = minObstaclePercentage;
                    }
                }
            }
            DrawRectangleRec(minusObstacleButton, Fade(GREEN, 0.8f));
            DrawText("-", static_cast<int>(minusObstacleButton.x + minusObstacleButton.width / 2 - MeasureText("-", obstaclePercentageFontSize) / 2),
                     static_cast<int>(minusObstacleButton.y + minusObstacleButton.height / 2 -
                                      obstaclePercentageFontSize / 2),
                     obstaclePercentageFontSize, BLACK);

            // Dibujar el botón "+" para aumentar el porcentaje de obstáculos
            Rectangle plusObstacleButton = {gridSizeTextPosX + gridSizeTextWidth / 2.0f + 5.0f,
                                            obstaclePercentageTextPosY + obstaclePercentageFontSize + 10.0f,
                                            gridSizeTextWidth / 2.0f - 5.0f, obstaclePercentageFontSize + 10.0f};
            if (percentage < maxObstaclePercentage)
            {
                if (CheckCollisionPointRec(GetMousePosition(), plusObstacleButton) &&
                    IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    percentage += obstaclePercentageStep;
                    if (percentage > maxObstaclePercentage)
                    {
                        percentage = maxObstaclePercentage;
                    }
                }
            }
            DrawRectangleRec(plusObstacleButton, Fade(GREEN, 0.8f));
            DrawText("+", static_cast<int>(plusObstacleButton.x + plusObstacleButton.width / 2 - MeasureText("+", obstaclePercentageFontSize) / 2),
                     static_cast<int>(plusObstacleButton.y + plusObstacleButton.height / 2 -
                                      obstaclePercentageFontSize / 2),
                     obstaclePercentageFontSize, BLACK);

            // Posiciones generales
            float AlgTextPosX = optionsColumn.x + optionsColumn.width / 2;
            float AlgTextPosY = obstaclePercentageTextPosY + obstaclePercentageFontSize + 10.0f;

            // Dibujar los botones de algoritmos
            algorithmButtons(AlgTextPosX, AlgTextPosY);

            // Dibujar el botón "Save" en la esquina inferior izquierda de la columna de opciones
            char *saveButtonText = "Save";

            if (created)
            {
                saveButtonText = "Save";
            }
            else
            {
                saveButtonText = "Create";
                gridSize = m_size;
            }

            float saveButtonFontSize = 24;
            float saveButtonTextWidth = MeasureText(saveButtonText, saveButtonFontSize);
            float saveButtonPosX = optionsColumn.x + optionsColumn.width / 2 - saveButtonTextWidth / 2 - 40;
            float saveButtonPosY = SCREENHEIGHT - 60 - saveButtonFontSize;
            Rectangle saveButton = {saveButtonPosX, saveButtonPosY, saveButtonTextWidth + 10, saveButtonFontSize + 10};

            if (CheckCollisionPointRec(GetMousePosition(), saveButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) &&
                !created && startCellX != -1 && startCellY != -1 && endCellX != -1 && endCellY != -1)
            {
                gridSize = m_size;
                obstaclePercentage = percentage;

                maze1->create(gridSize, gridSize);
                maze2->create(gridSize, gridSize);

                maze1->setStart(startCellX, startCellY);
                maze1->setEnd(endCellX, endCellY);
                maze1->generateRandomMaze(obstaclePercentage);

                maze2->copyMaze(*maze1);

                created = true;
                con_obstaculos = true;
            }
            if (CheckCollisionPointRec(GetMousePosition(), saveButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && created)
            {
                maze1->create(gridSize, gridSize);
                maze2->create(gridSize, gridSize);

                maze1->setStart(startCellX, startCellY);
                maze1->setEnd(endCellX, endCellY);
                maze1->generateRandomMaze(percentage);

                maze2->copyMaze(*maze1);

                con_obstaculos = true;
                saved = true;
            }
            DrawRectangleRec(saveButton, Fade(ORANGE, 0.8f));
            DrawText(saveButtonText, saveButtonPosX + 5, saveButtonPosY + 5, saveButtonFontSize, BLACK);

            // Dibujar el botón "Run" en la esquina inferior derecha de la columna de opciones
            const char *runButtonText = "Run";
            float runButtonFontSize = 24;
            float runButtonTextWidth = MeasureText(runButtonText, runButtonFontSize);
            float runButtonPosX = optionsColumn.x + optionsColumn.width / 2 - saveButtonTextWidth / 2 + 40;
            float runButtonPosY = SCREENHEIGHT - 60 - saveButtonFontSize;
            Rectangle runButton = {runButtonPosX, runButtonPosY, runButtonTextWidth + 10, runButtonFontSize + 10};


            if (created && algorithms.size() > 1)
            {
                DrawRectangleRec(runButton, Fade(LIME, 0.8f));
                DrawText(runButtonText, runButtonPosX + 5, runButtonPosY + 5, runButtonFontSize, BLACK);
                if (saved && startCellX != -1 && startCellY != -1 && endCellX != -1 && endCellY != -1)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), runButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        runned = true;

                        if (algorithms[0] == "Dijsktra")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze1->dijkstra();
                            auto end = std::chrono::high_resolution_clock::now();

                            time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[0] == "A* Eu")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze1->astarEuclidean();
                            auto end = std::chrono::high_resolution_clock::now();

                            time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[0] == "A* Mh")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze1->astarManhattan();
                            auto end = std::chrono::high_resolution_clock::now();

                            time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[0] == "G-BFS Eu")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze1->greedyBFSEuclidean();
                            auto end = std::chrono::high_resolution_clock::now();

                            time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[0] == "G-BFS Mh")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze1->greedyBFSManhattan();
                            auto end = std::chrono::high_resolution_clock::now();

                            time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }

                        if (algorithms[1] == "Dijsktra")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze2->dijkstra();

                            auto end = std::chrono::high_resolution_clock::now();

                            time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[1] == "A* Eu")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze2->astarEuclidean();
                            auto end = std::chrono::high_resolution_clock::now();

                            time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[1] == "A* Mh")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze2->astarManhattan();
                            auto end = std::chrono::high_resolution_clock::now();

                            time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[1] == "G-BFS Eu")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze2->greedyBFSEuclidean();
                            auto end = std::chrono::high_resolution_clock::now();

                            time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }
                        else if (algorithms[1] == "G-BFS Mh")
                        {
                            auto start = std::chrono::high_resolution_clock::now();
                            maze2->greedyBFSManhattan();

                            auto end = std::chrono::high_resolution_clock::now();

                            time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                        }

                        con_visitados = true;
                    }
                }
                else
                {
                    runned = false;
                }
            }

            //Dibujar el botón "Reset" en la esquina inferior izquierda debajo de save
            const char *resetButtonText = "Reset";
            float resetButtonFontSize = 24;
            float resetButtonTextWidth = MeasureText(resetButtonText, resetButtonFontSize);
            float resetButtonPosX = optionsColumn.x + optionsColumn.width / 2 - resetButtonTextWidth / 2;
            float resetButtonPosY = SCREENHEIGHT - 60 - saveButtonFontSize - 60;
            Rectangle resetButton = {resetButtonPosX, resetButtonPosY+100, resetButtonTextWidth + 10, resetButtonFontSize + 10};

            if (startCellX != -1 || startCellY != -1 || endCellX != -1 || endCellY != -1){
                DrawRectangleRec(resetButton, Fade(RED, 0.8f));
                DrawText(resetButtonText, resetButtonPosX + 5, resetButtonPosY + 105, resetButtonFontSize, BLACK);

                if (CheckCollisionPointRec(GetMousePosition(), resetButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    startCellX = -1;
                    startCellY = -1;
                    endCellX = -1;
                    endCellY = -1;
                    saved = false;
                    runned = false;
                    con_visitados = false;
                    con_obstaculos = false;
                    gridSize = 20.0f;
                    m_size = 20.0f;
                    created = false;
                    percentage = 0.2f;
                    obstaclePercentage = 0.2f;

                    marker1 = " ";
                    marker2 = " ";
                    marker3 = " ";
                    marker4 = " ";
                    marker5 = " ";

                    algorithms.clear();
                }
            }

            drawGrids(optionsColumn);

            EndDrawing();
        }
    }
}
