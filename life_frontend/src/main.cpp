#include "life_backend.h"
#include "life_frontend.h"
#include <string>
#include "Windows.h"


void resizeWindow(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, int &cellSizeX, int &cellSizeY, int newWidth, int newHeight) {
    int numRows = life.getHeight();
    int numCols = life.getWidth();
    cellSizeX = newWidth / numCols;
    cellSizeY = newHeight / numRows;
    front.SDL_SetWindowSize(window, cellSizeX*numCols, cellSizeY*numRows);
}


void draw(life_backend::Life &life, int cellSizeX, int cellSizeY, int xMouse, int yMouse, const char action) {
    int x = xMouse / cellSizeX;
    int y = yMouse / cellSizeY;

    switch (action) {
        case 'D':
            life.setCellAlive(x, y);
            break;
        case 'C':
            life.setCellDead(x ,y);
            break;
    }
}

void renderWindowWithGrid(SDL_Renderer *renderer, life_frontend::life_frontend &front, life_backend::Life &life,
                          int cellSizeX, int  cellSizeY) {
    int numRows = life.getHeight();
    int numCols = life.getWidth();

    for (int x = 0; x < numCols; ++x) {
        for (int y = 0; y < numRows; ++y) {
            if (life.getCellState(x, y)) {
                front.SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Устанавливаем цвет клетки белым
            } else {
                front.SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Устанавливаем цвет клетки черным
            }

            SDL_Rect cellRect = {x * cellSizeX, y * cellSizeY, cellSizeX, cellSizeY};
            front.SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    front.SDL_RenderPresent(renderer);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    const std::string lib_path = "C:\\Users\\user\\CLionProjects\\GTT\\cmake-build-debug\\SDL2.dll";
    life_frontend::life_frontend front(lib_path);

    life_backend::Life life(150, 150);
    int cellSizeX = 5;
    int cellSizeY = 5;
    int width = life.getWidth();
    int height = life.getHeight();

    front.SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = front.SDL_CreateWindow("[Game of shiza] FPS: 10", SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width * cellSizeX, height * cellSizeY, SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = front.SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    front.SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    front.SDL_RenderClear(renderer);

    SDL_Event event;
    bool quit = false;
    bool playing = true;
    bool reTitle = false;
    bool isMeme = false;
    bool picture = false;
    bool isDraw = false;
    char action;
    int ms = 100;
    while (!quit) {
        while (front.SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) action = 'D';
                else action = 'C';
                isDraw = true;
                playing = false;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                isDraw = false;
            }
            if (event.type == SDL_MOUSEMOTION && isDraw) {
                draw(life, cellSizeX, cellSizeY, event.motion.x, event.motion.y, action);
            }
            if(event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    int newWidth = event.window.data1;
                    int newHeight = event.window.data2;
                    resizeWindow(window, front, life, cellSizeX, cellSizeY, newWidth, newHeight);
                }
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_p:
                        playing = !playing;
                        reTitle = true;
                        break;
                    case SDLK_x:
                        life.clear();
                        break;
                    case SDLK_r:
                        life.fillRandomStates();
                        break;
                    case SDLK_t:
                        if (life.fillCoolestStates()) {
                            playing = false;
                            picture = true;
                        }
                        break;
                    case SDLK_s:
                        if (life.USSR()) {
                            playing = false;
                            picture = true;
                        }
                        break;
                    case SDLK_KP_MINUS:
                        if (ms < 1000) {
                            ms += 10;
                            reTitle = true;
                        }
                        break;
                    case SDLK_KP_PLUS:
                        if (ms > 10) {
                            ms -= 10;
                            reTitle = true;
                        }
                        break;
                    case SDLK_6:
                        if (isMeme) {
                            reTitle = true;
                            isMeme = false;
                        } else {
                            int FPS = 1000 / ms;
                            std::string title = "[ГЕЙМ ОФ ШИЗА] ФПС: " + std::to_string(FPS);
                            front.SDL_SetWindowTitle(window, title.c_str());
                            isMeme = true;
                        }
                        break;
                }
            }
        }

        if (reTitle) {
            int FPS = 1000 / ms;
            std::string title = "[Game of shiza] FPS: " + std::to_string(FPS);
            front.SDL_SetWindowTitle(window, title.c_str());
            reTitle = false;
        }

        if (picture || isDraw) {
            renderWindowWithGrid(renderer, front, life, cellSizeX, cellSizeY);
            picture = false;
        }

        if (playing) {
            life.updateCellStates();
            renderWindowWithGrid(renderer, front, life, cellSizeX, cellSizeY);
            front.SDL_Delay(ms);
        } else {
            std::string title = "[Game of shiza] PAUSED";
            front.SDL_SetWindowTitle(window, title.c_str());
        }
    }
    front.SDL_DestroyWindow(window);
    front.SDL_Quit();
    return 0;
}

