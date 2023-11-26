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
  * Создавать на поел мертвые клетки
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
 ___

# Задачи
* До конца разобраться с библиотеками (SDL2)
* Реализовать кросс-платформенность
* Завершить файлы сборки (CMakeLists.txt)
  * GoogleTests
  * BackEnd
  * FrontEnd
  * Main Progect
* Дописать необходимые функции для frontend'а (по надобности)
* Дописать функионал backend'а для увеличения размера поля
* Отладить main.cpp
  * Разнести функционал по отдельным функциям
  * Сделать флаги и постоянные значения статическими
    * cellSizeX
    * cellSizeY
    * ms
    * action (вероятно, заменить на bool)
    * quit
    * playing
    * reTitle
    * isMeme
    * picture
    * isDraw
* Добавить иконку прихожения
* Разобраться в запуске приложения на устройствах без компилятора (возможно ли?)

___
___

# Полезное
* [SDL2 Wiki](https://wiki.libsdl.org/SDL2/FrontPage/ "Документация по SDL2")
* [SDL2 Guide](https://habr.com/ru/articles/453700/ "Уроки по SDL2")
* [SDL2 Documentation](https://tr0ll.net/libsdl/docs/sdldoc.pdf "Документация по SDL2 v2")
* Есть программа по "преобразованию" функций SDL2 в функии frontend
* Есть программа по переводу пиксельных изображений в нашу игру
