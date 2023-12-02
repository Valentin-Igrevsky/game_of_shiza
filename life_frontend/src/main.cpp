#include "life_backend.h"
#include "life_frontend.h"
#include <string>
#include "Windows.h"

static int R = 255;
static int G = 0;
static int B = 0;
static int RGBid = 3;
static std::vector<int> speedRGB = {1, 5, 17, 51, 85};
static bool quit = false;
static bool reTitle = false;
static bool reRender = false;
static bool reRenderWin = true;
static bool isPlay = true;
static bool isMeme = false;
static bool isDraw = false;
static bool isShift = false;
static bool isRGB = false;
static char action;
static int cellSizeX = 15;
static int cellSizeY = 15;
static int ms = 100;
static std::string title;

void calculateRGB() {
    if (R == 255 && B == 0 && G != 255) G += speedRGB[RGBid];
    else if (G == 255 && B == 0 && R != 0) R -= speedRGB[RGBid];
    else if (R == 0 && G == 255 && B != 255) B += speedRGB[RGBid];
    else if (R == 0 && B == 255 && G != 0) G -= speedRGB[RGBid];
    else if (G == 0 && B == 255 && R != 255) R += speedRGB[RGBid];
    else if (R == 255 && G == 0 && B != 0) B -= speedRGB[RGBid];
}

void createNewTitle() {
    if (isMeme) title = "ГЕЙМ ОФ ШИЗА";
    else title = "Game of shiza";

    if (!isPlay) title += " [PAUSED]";
    else {
        int FPS = 1000 / ms;
        title += " [ФПС: " + std::to_string(FPS) + "]";
    }

    if (isShift) title += " [Mod: Resize]";
    else title += " [Mod: Scale]";

    if (isRGB) title += " [RGB: ON]";
    else title += " [RGB: OFF]";
}

void resizeGame(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, int newWidth, int newHeight) {
    int newCols = newWidth / cellSizeX;
    int newRows = newHeight / cellSizeY;
    life.resize(newCols, newRows);
    front.SDL_SetWindowSize(window, cellSizeX * newCols + 1, cellSizeY * newRows + 1);
    reRenderWin = true;
}

void resizeWindow(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, int newWidth, int newHeight) {
    int numRows = static_cast<int>(life.getHeight());
    int numCols = static_cast<int>(life.getWidth());
    cellSizeX = newWidth / numCols;
    cellSizeY = newHeight / numRows;
    front.SDL_SetWindowSize(window, cellSizeX * numCols + 1, cellSizeY * numRows + 1);
    reRenderWin = true;
}


void draw(life_backend::Life &life, int xMouse, int yMouse) {
    int x = xMouse / cellSizeX;
    int y = yMouse / cellSizeY;
    if (x >= 0 && x < life.getWidth() && y >= 0 && y < life.getHeight()) {
        switch (action) {
            case 'D':
                life.setCellAlive(x, y);
                break;
            case 'C':
                life.setCellDead(x, y);
                break;
        }
    }

}

void renderWindowWithGrid(SDL_Renderer *renderer, life_frontend::life_frontend &front, life_backend::Life &life) {

    if (reRenderWin) {
        front.SDL_SetRenderDrawColor(renderer, R, G, B, 255);
        front.SDL_RenderClear(renderer);
        front.SDL_RenderPresent(renderer);
        reRenderWin = false;
    }

    int numRows = life.getHeight();
    int numCols = life.getWidth();

    if (!isDraw && isRGB) {
        calculateRGB();
        front.SDL_SetRenderDrawColor(renderer, R, G, B, 255);
    } else {
        front.SDL_SetRenderDrawColor(renderer, 0, 115, 25, 255);
    }

    SDL_Rect cellRect = {0, 0, numCols * cellSizeX + 1, numRows * cellSizeY + 1};
    front.SDL_RenderFillRect(renderer, &cellRect);

    for (int x = 0; x < numCols; ++x) {
        for (int y = 0; y < numRows; ++y) {
            if (life.getCellState(x, y)) {
                front.SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                front.SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            cellRect = {x * cellSizeX + 1, y * cellSizeY + 1, cellSizeX - 1, cellSizeY - 1};
            front.SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    front.SDL_RenderPresent(renderer);
}

void events(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        quit = true;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) action = 'D';
        else action = 'C';
        draw(life, event.button.x, event.button.y);
        isDraw = true;
        isPlay = false;
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        isDraw = false;
    }
    if (event.type == SDL_MOUSEMOTION && isDraw) {
        draw(life, event.motion.x, event.motion.y);
    }
    if (event.type == SDL_WINDOWEVENT) {
        if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;
            if (isShift) {
                resizeGame(window, front, life, newWidth, newHeight);
            } else {
                resizeWindow(window, front, life, newWidth, newHeight);
            }
            reRender = true;
        }
    }


    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_p:
                isPlay = !isPlay;
                reTitle = true;
                break;
            case SDLK_x:
                life.clear();
                reRender = true;
                break;
            case SDLK_r:
                life.fillRandomStates();
                reRender = true;
                break;
            case SDLK_t:
                if (life.fillCoolestStates()) {
                    isPlay = false;
                    reRender = true;
                }
                break;
            case SDLK_s:
                if (life.USSR()) {
                    isPlay = false;
                    reRender = true;
                }
                break;
            case SDLK_z:
                if (life.ZRUSZ()) {
                    isPlay = false;
                    reRender = true;
                }
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
                isMeme = !isMeme;
                reTitle = true;
                break;
            case SDLK_COMMA:
                if (RGBid > 0) {
                    RGBid -= 1;
                    R = 255;
                    G = 0;
                    B = 0;
                }
                break;
            case SDLK_PERIOD:
                if (RGBid < 4) {
                    RGBid += 1;
                    R = 255;
                    G = 0;
                    B = 0;
                }
                break;
            case SDLK_LSHIFT:
                isShift = !isShift;
                reTitle = true;
                break;
            case SDLK_c:
                isRGB = !isRGB;
                reTitle = true;
                break;
        }
    }
}

/// "esc" - escape
/// "p" - pause
/// "x" - clear
/// "r" - random fill
/// "+" - FPS up
/// "-" - FPS down
/// ">" - RGB speed up
/// "<" - RGB speed down
/// "6" - meme
/// LMB - set alive cell
/// RMB - set ded cell
/// MB + move - draw with type of cell


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    const std::string lib_path = "C:\\Users\\user\\CLionProjects\\GTT\\cmake-build-debug\\SDL2.dll";
    life_frontend::life_frontend front(lib_path);

    life_backend::Life life(15, 15);

    int width = life.getWidth();
    int height = life.getHeight();

    createNewTitle();

    front.SDL_Init(SDL_INIT_VIDEO);


    SDL_Window *window = front.SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width * cellSizeX + 1, height * cellSizeY + 1,
                                                SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = front.SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    while (!quit) {
        while (front.SDL_PollEvent(&event)) {
            events(window, front, life, event);
        }

        if (reTitle) {
            createNewTitle();
            front.SDL_SetWindowTitle(window, title.c_str());
            reTitle = false;
        }

        if (reRender || isDraw) {
            renderWindowWithGrid(renderer, front, life);
            reRender = false;
        }

        if (isPlay) {
            life.updateCellStates();
            renderWindowWithGrid(renderer, front, life);
            front.SDL_Delay(ms);
        } else {
            front.SDL_Delay(1);
        }
    }

    front.SDL_DestroyWindow(window);
    front.SDL_Quit();
    return 0;
}