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
* Обновлен CMakeLists.txt: frontend
* Обновлен CMakeLists.txt: gtests
* Обновлен CMakeLists.txt: main project

 ___
 ___

# Задачи
* До конца разобраться с библиотеками (SDL2)
* Реализовать кросс-платформенность
* Завершить файлы сборки (CMakeLists.txt)
  * FrontEnd
* Дописать необходимые функции для frontend'а (по надобности)
* Добавить музыку
* Разобраться в запуске приложения на устройствах без компилятора (возможно ли?)

___
___

# Полезное
* [SDL2 Wiki](https://wiki.libsdl.org/SDL2/FrontPage/ "Документация по SDL2")
* [SDL2 Guide](https://habr.com/ru/articles/453700/ "Уроки по SDL2")
* [SDL2 Documentation](https://tr0ll.net/libsdl/docs/sdldoc.pdf "Документация по SDL2 v2")
* Есть программа по "преобразованию" функций SDL2 в функии frontend
* Есть программа по переводу пиксельных изображений в нашу игру
