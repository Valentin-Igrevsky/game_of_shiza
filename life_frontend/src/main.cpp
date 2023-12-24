#ifdef APPLE
#include <mach-o/dyld.h>
#endif
#if defined(_WIN32)

#include <windows.h>

#else
#include <unistd.h>
#endif

#include <filesystem>
#include "variables.h"


#include "life_backend.h"
#include "life_frontend.h"

#include <thread>

namespace {
    std::filesystem::path getExecutablePath() {
        char path[1024];
#if defined(_WIN32) || defined(_WIN64)
        GetModuleFileName(NULL, path, sizeof(path));
        return std::string(path);
#elif defined(__linux__)
        ssize_t len = ::readlink("/proc/self/exe", path, sizeof(path) - 1);
        if (len != -1)
        {
            path[len] = '\0';
            return std::string(path);
        }
#elif defined(__APPLE__)
        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) == 0) {
            return std::filesystem::path(std::string(path));
        }
#endif

        return std::string();
    }
}

auto pathToExecutable = ::getExecutablePath();
auto pathToDirWhereExecutable = std::filesystem::path(pathToExecutable.string()).parent_path().parent_path();
std::string SDL_LIBRARY_NAME = MY_VARIABLE;
std::string SDL2MIXER_LIBRARY_NAME = SDL2MIXER;
static auto pathToSdlLibrary = pathToDirWhereExecutable / "life_frontend" / MY_VARIABLE;
static auto pathToSdl2MixerLibrary = pathToDirWhereExecutable / "life_frontend" / SDL2MIXER;

static int R = 255;
static int G = 0;
static int B = 0;
static int RGBid = 3;
static std::vector<int> speedRGB = {1, 5, 17, 51, 85};
static bool quit = false;
static bool reTitle = false;
static bool reRender = false;
static bool isPlay = true;
static bool isMeme = false;
static bool isDraw = false;
static bool isShift = false;
static bool isRGB = false;
static bool isPlayMusic = false;
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

void resizeGame(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, int newWidth,
                int newHeight) {
    int newCols = newWidth / cellSizeX;
    int newRows = newHeight / cellSizeY;
    life.resize(newCols, newRows);
    front.SDL_SetWindowSize(window, cellSizeX * newCols + 1, cellSizeY * newRows + 1);
}

void resizeWindow(SDL_Window *window, life_frontend::life_frontend &front, life_backend::Life &life, int newWidth,
                  int newHeight) {
    int numRows = static_cast<int>(life.getHeight());
    int numCols = static_cast<int>(life.getWidth());
    cellSizeX = newWidth / numCols;
    cellSizeY = newHeight / numRows;
    front.SDL_SetWindowSize(window, cellSizeX * numCols + 1, cellSizeY * numRows + 1);
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
            case SDLK_m:
                isPlayMusic = true;
        }
    }
}

void play_game() {
    life_frontend::life_frontend front(pathToSdlLibrary.string());

    life_backend::Life life(15, 15);

    int width = life.getWidth();
    int height = life.getHeight();

    createNewTitle();

    front.SDL_Init(SDL_INIT_VIDEO);


    SDL_Window *window = front.SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width * cellSizeX + 1, height * cellSizeY + 1,
                                                SDL_WINDOW_RESIZABLE);

    SDL_Surface *icon = front.SDL_LoadBMP_RW(front.SDL_RWFromFile("lenya.bmp", "rb+"), 1);  // ленька
    if (icon != nullptr) {
        front.SDL_SetWindowIcon(window, icon);
        front.SDL_FreeSurface(icon);
    }

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
}

void play_music() {
    life_frontend::SDL_MUSIC sdl_music(pathToSdl2MixerLibrary.string());

    sdl_music.Mix_Init(SDL_INIT_AUDIO);

//    sdl_music.Mix_Init(MIX_INIT_OGG);


    sdl_music.Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Music *music = sdl_music.Mix_LoadMUS("Freddy.wav");

    sdl_music.Mix_Volume(-1, MIX_MAX_VOLUME);
    sdl_music.Mix_VolumeMusic(MIX_MAX_VOLUME);

    while(!quit) {
        if (!sdl_music.Mix_PlayingMusic()) {
            sdl_music.Mix_PlayMusic(music, 10);
        }
    }

    sdl_music.Mix_FreeMusic(music);

    sdl_music.Mix_CloseAudio();
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

#if defined(_WIN32) || defined(_WIN64)
    int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#elif defined(__linux__)
    int main(int argc, char **argv)
#endif
{
//    life_frontend::life_frontend front(pathToSdlLibrary.string());
//    life_frontend::SDL_MUSIC sdl_music(pathToSdl2MixerLibrary.string());

//    life_backend::Life life(15, 15);
//
//    int width = life.getWidth();
//    int height = life.getHeight();

//    createNewTitle();

//    front.SDL_Init(SDL_INIT_VIDEO);
//    sdl_music.Mix_Init(SDL_INIT_AUDIO);
//
//    sdl_music.Mix_Init(MIX_INIT_MP3);
//
//    sdl_music.Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
//
//    Mix_Music *music = sdl_music.Mix_LoadMUS("C:\\Users\\user\\CLionProjects\\GTT\\life_frontend\\src\\Freddy.wav");
//    if (!music) {
//        std::cerr << "Ошибка загрузки музыки: " << front.Mix_GetError() << std::endl;
//    } else {
//        front.Mix_PlayMusic(music, 10);
//    }

//    sdl_music.Mix_VolumeMusic(100);


//    SDL_Window *window = front.SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
//                                                SDL_WINDOWPOS_CENTERED,
//                                                width * cellSizeX + 1, height * cellSizeY + 1,
//                                                SDL_WINDOW_RESIZABLE);

//    SDL_Surface *icon = front.SDL_LoadBMP_RW(front.SDL_RWFromFile("lenya.bmp", "rb+"), 1);  // ленька
//    if (icon != nullptr) {
//        front.SDL_SetWindowIcon(window, icon);
//        front.SDL_FreeSurface(icon);
//    }
//
//    SDL_Renderer *renderer = front.SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



//    SDL_Event event;
//    while (!quit) {
//        sdl_music.Mix_PlayMusic(music, 100);
//
//        while (front.SDL_PollEvent(&event)) {
//            events(window, front, life, event);
//        }
//
//        if (reTitle) {
//            createNewTitle();
//            front.SDL_SetWindowTitle(window, title.c_str());
//            reTitle = false;
//        }
//
//        if (reRender || isDraw) {
//            renderWindowWithGrid(renderer, front, life);
//            reRender = false;
//        }
//
//        if (isPlay) {
//            life.updateCellStates();
//            renderWindowWithGrid(renderer, front, life);
//            front.SDL_Delay(ms);
//        } else {
//            front.SDL_Delay(1);
//        }
//    }
//    sdl_music.Mix_FreeMusic(music);
//
//    // Закрытие аудио SDL2_mixer
//    sdl_music.Mix_CloseAudio();

//    front.SDL_DestroyWindow(window);
//    front.SDL_Quit();

    std::thread game_thread(play_game);
    std::thread music_thread(play_music);

    game_thread.join();
    music_thread.join();

    return 0;
}
//}