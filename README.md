# Обновления проекта
### [UPD v1.0](https://github.com/Valentin-Igrevsky/game_of_jiza/commit/4858da094bcf122f49654313ea27ddec35f5aa75/ "backend, gtest")
* Добавлен backend
* Подлючена библиотека GoogleTests
* Добавлены тесты

___

### [UPD v1.1](https://github.com/Valentin-Igrevsky/game_of_jiza/commit/1c259fb1acdfba97d6ec614ff0ebf1a45d4f21ef/ "удалил прагма уанс в life.cpp")
* Поправлен backend
* Добавлены новые тесты

___

### [UPD v2.0](https://github.com/Valentin-Igrevsky/game_of_jiza/commit/63ba563682e90336c6b84b9094a218c86b02f974/ "UPD backend, ADD frontend")
* Подключена библиотека SDL2
* Настроены CMakeLists.txt проекта
* Добавлен функционал backend'а
* Добавлен frontend
* Написан рендер онка для игры
* Написана функция заполнения игрового поля (окна) клетками
* Добавлены:
  * Выход из игры
  * Пауза
  * Очистка поля
  * Рандомное заполнение поля
  * Увеличение и понижение FPS
  * Динамическое изменения заголовка окна
  * Some Memes
* Реализованы возможности:
  * Создавать на поле живые клетки
  * Создавать на поле мертвые клетки
  * Масштабировать окно

___

### [UPD v2.1](https://github.com/Valentin-Igrevsky/game_of_jiza/commit/5ba9ab63a212d94eb9f1d0727cdb8e900f788dbf/ "commit SDL2 lib")
* В удаленный репозиторий добавлена библиотека SDL2

___

### [UPD v2.2](https://github.com/Valentin-Igrevsky/game_of_jiza/commit/806e67b6db4d8bb4efe34ea46152249e310502c9/ "add README.md")
* Добавлен README.md
  * Patch note
  * Tasks

___

### [UPD v2.3](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/6df6b6388400d41b2e8317f69e917cdf9a98c612/ "BugFix, Main-separation, RGB, WinResize, GameResize")
* В backend добавлен метод resize
* Поправлена ошибка: вылет игры при выходе мышью за границы окна
* Поправлена ошибка: зависание игры при переходе в другое окно
* Флаги и остальные переменные расчета значений сделаны статическими
* Main разделен на отдельные функции
* Добавлена RGB-подсветка
* Добавлен Scale окна
* Добавлен Resize окна

___

### [UPD v3.0](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/b875f6dc27ffdd566116c67cc3b340e5e9c828d3/ "new CMAKE, add backend tests, add icon, bug fix")
* Поправлена ошибка: мограние экрана при расширении на весь экран
* Добавлены новые тесты
* Добавлен новый функционал frontend'а
* Добавлена иконка
* SDL2 перенесена в отдельную папку
* Обновлен CMakeLists.txt:
  * frontend 
  * gtests
  * main project

___

### UPD v3.1 (SDL2_mixer, Music)

#### [UPD v3.1.1](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/eb0dc03141eb88a03560b3dd5718f2631f47b8c3/ "Нерабочая музыка 1")
* Добавлен функционал SDL2_mixer
* Добавлены настройки SDL2_mixer в CMakeLists.txt

#### [UPD v3.1.2](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/c68ff77ae21dbf0177cdb1049df9b8bdc2508fd0/ "Нерабочая музыка 2")
* Добавлен заголовочный файл SDL2_mixer

#### [UPD v3.1.2](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/d6450eaf417ce4a7a1289dfa296a0260f8ffdfdb/ "Нерабочая музыка 3")
* Добавлена библиотека SDL2_mixer.dll
* Добавлен проигрываемый файл

#### [UPD v3.1.3](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/2138807a40547b98259d445a4f85fcd94fc400ac/ "UPD Cross-Platform")
* Функционал frontend'а была разделен на два отдельных класса
  * life_frontend
  * SDL_MUSIC
* Функция main разделена на две функции
  * play_game()
  * play_music()
* Добавлена многопоточная обработка рендера и музыки
* Настроено опеределени нужных функций для работы с библиотеками в зависимости от ОС
  * GET_PROC_ADDRESS
  * LOAD_LIBRARY
  * FREE_LIBRARY
* Настроено определение архитектуры
  * x86
  * x86-64
  * AMD64
  * ARM
  * ARM64
* Настроено определение путей до библиотек в Linux

___

### [UPD v3.2](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/c226935710c25620c6df769ce10422ae9161267d/ "UPD Cross-Platform 3")
* Почищены файлы frontend'а
* Почищен файл main
* Добавлена возможность повышать/понижать громкость звука
* Настроено изменение заголовка окна

___

### UPD v3.3 (Linux)

#### [UPD v3.3.1](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/443ff3110b16d9a54d23f15b7e888fcf1a6263ac/ "UPD Cross-Platform 4")
* Донастроено опеределени нужных функций для работы с библиотеками в зависимости от ОС
  * HANDLER
  * sdl_lib_handle
  * sdl2mixer_lib_handle
* Настроен CMakeLists.txt для работы на Linux

#### [UPD v3.3.1](https://github.com/Valentin-Igrevsky/game_of_shiza/commit/c004e2d32382cec24cc0c5e97d24829bfac003fe/ "ADD .so files")
* Добавлены:
  * libSDL2.so
  * libSDL2_mixer.so

___
___

# Задачи
* До конца почистить файлы
* Сделать из frontend.cpp библиотеки .dll и .os (?)
  * Переделать frontend.cpp
  * Переделать CMakeLists.txt
  * Переделать пол проекта

___
___

# Полезное
* [SDL2 Wiki](https://wiki.libsdl.org/SDL2/FrontPage/ "Документация по SDL2")
* [SDL2 Guide](https://habr.com/ru/articles/453700/ "Уроки по SDL2")
* [SDL2 Documentation](https://tr0ll.net/libsdl/docs/sdldoc.pdf "Документация по SDL2 v2")
* Есть программа по "преобразованию" функций SDL2 и SDL2_mixer в функии frontend
* Есть программа по переводу пиксельных изображений в нашу игру
