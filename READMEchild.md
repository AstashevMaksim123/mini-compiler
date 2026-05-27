# Очень подробная инструкция по запуску проекта "с флешки"

Этот файл написан для человека, который получил проект как папку на флешке и раньше его не запускал.

Ниже описано:

- куда скопировать проект;
- что установить;
- как собрать компилятор;
- как проверить, что всё работает;
- как прогнать обычные тесты;
- как прогнать новые большие showcase-тесты;
- где смотреть `.ll`, `.o` и `.s` файлы.

## 1. Что у вас должно быть

Проект рассчитан на:

- Linux
- или WSL2 с Ubuntu под Windows

Если вы работаете в Windows без WSL, сначала лучше установить WSL2 с Ubuntu, потому что команды и сборка рассчитаны именно на Linux-среду.

## 2. Куда положить папку проекта

Если проект у вас на флешке, не запускайте его прямо с флешки.

Лучше скопировать папку целиком на диск, например:

- в Linux: `/home/<ваше_имя>/projects/mini_compiler`
- в WSL Ubuntu: `/home/<ваше_имя>/projects/mini_compiler`

Пример:

```bash
mkdir -p ~/projects
cp -r /media/$USER/FLASH_DRIVE/mini_compiler ~/projects/
```

Если вы в WSL и флешка видна через Windows-диск, путь может быть примерно такой:

```bash
mkdir -p ~/projects
cp -r /mnt/d/mini_compiler ~/projects/
```

После копирования перейдите в папку проекта:

```bash
cd ~/projects/mini_compiler
```

Проверьте, что вы действительно в нужной папке:

```bash
pwd
ls
```

Вы должны увидеть среди файлов:

- `CMakeLists.txt`
- `README.md`
- `READMEchild.md`
- `compiler_answers.md`
- папки `src`, `include`, `runtime`, `tests`, `scripts`

## 3. Что нужно установить

Проект использует:

- `cmake`
- `make`
- `clang`
- `llvm`
- `llvm-dev`
- `flex`
- `bison`

Для Ubuntu установите всё одной командой:

```bash
sudo apt update
sudo apt install -y cmake make clang llvm llvm-dev flex bison
```

Если система спросит пароль, введите пароль вашего пользователя.

## 4. Как проверить, что зависимости установились

Выполните:

```bash
cmake --version
clang --version
llvm-config --version
llvm-nm --version
flex --version
bison --version
```

Если все команды отработали и напечатали версии, значит зависимости установлены нормально.

## 5. Как устроен проект

Главные части проекта:

- `src/lexer.l` — лексер на Flex
- `src/parser.y` — парсер на Bison
- `include/ast.hpp`, `src/ast.cpp` — AST
- `include/sema.hpp`, `src/sema.cpp` — семантика
- `include/codegen.hpp`, `src/codegen.cpp` — генерация LLVM IR
- `include/object_emitter.hpp`, `src/object_emitter.cpp` — выпуск `.o`
- `src/driver.cpp` — команда `mini_cc`
- `runtime/main.c` — внешний `main`, который вызывает `compiled_fn`
- `tests/positive` — обычные позитивные тесты
- `tests/negative` — негативные тесты с ошибками
- `tests/showcase` — новые более крупные тестовые программы
- `scripts/run_tests.sh` — автоматический прогон тестов

## 6. Как собрать проект

Из корня проекта выполните:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

Если всё хорошо, в конце появится исполняемый файл:

```bash
./mini_cc
```

Можно проверить, что он существует:

```bash
ls -l mini_cc
```

## 7. Самая первая проверка: собрать один пример вручную

Находясь в папке `build`, выполните:

```bash
./mini_cc ../tests/positive/switch_default.mc --emit-ir -o generated.o
```

После этого должны появиться:

- `generated.o`
- `generated.ll`

Проверьте:

```bash
ls -l generated.o generated.ll
```

## 8. Как проверить, что экспортируется функция compiled_fn

Выполните:

```bash
llvm-nm generated.o
```

Среди символов должен быть:

```text
T compiled_fn
```

Это означает, что объектный файл экспортирует нужную функцию.

## 9. Как слинковать результат с runtime/main.c

Из папки `build` выполните:

```bash
clang ../runtime/main.c generated.o -o demo_app
```

После этого появится исполняемый файл:

```bash
./demo_app
```

Если всё собрано правильно, программа напечатает число.

## 10. Как прогнать все обычные тесты

Из корня проекта:

```bash
./scripts/run_tests.sh
```

Или из папки `build`:

```bash
../scripts/run_tests.sh
```

Этот скрипт:

- пересобирает проект;
- прогоняет тесты из `tests/positive`;
- прогоняет тесты из `tests/negative`;
- прогоняет тесты из `tests/showcase`;
- линкует позитивные программы с `runtime/main.c`;
- запускает полученные исполняемые файлы;
- проверяет ожидаемый вывод;
- проверяет ожидаемые сообщения об ошибках;
- генерирует `.s` для showcase-программ.

## 11. Как отдельно прогнать новые большие showcase-тесты

Если вы уже выполнили:

```bash
./scripts/run_tests.sh
```

то showcase-тесты уже были запущены автоматически.

Но если вы хотите посмотреть сами файлы, они лежат здесь:

```bash
ls tests/showcase
```

Там есть:

- `control_flow_showcase.mc`
- `nested_calls_and_scopes.mc`
- `loop_switch_aggregation.mc`

## 12. Где появляются `.s` файлы новых showcase-тестов

После запуска тестов:

```bash
./scripts/run_tests.sh
```

ассемблерные файлы появляются в:

```bash
build/showcase_asm
```

Проверить:

```bash
ls -l build/showcase_asm
```

Обычно вы увидите:

- `control_flow_showcase.s`
- `nested_calls_and_scopes.s`
- `loop_switch_aggregation.s`

## 13. Как вручную собрать один showcase-тест и получить `.ll`, `.o`, `.s`

Пример для `control_flow_showcase.mc`.

Из папки `build`:

```bash
./mini_cc ../tests/showcase/control_flow_showcase.mc --emit-ir -o control_flow_showcase.o
```

После этого появятся:

- `control_flow_showcase.o`
- `control_flow_showcase.ll`

Теперь превратим `.ll` в `.s`:

```bash
clang -S control_flow_showcase.ll -o control_flow_showcase.s
```

Проверим, что файлы есть:

```bash
ls -l control_flow_showcase.o control_flow_showcase.ll control_flow_showcase.s
```

Теперь слинкуем:

```bash
clang ../runtime/main.c control_flow_showcase.o -o control_flow_showcase_app
```

И запустим:

```bash
./control_flow_showcase_app
```

## 14. Как вручную прогнать все 3 showcase-программы по одной

Находясь в папке `build`, выполните:

```bash
./mini_cc ../tests/showcase/control_flow_showcase.mc --emit-ir -o control_flow_showcase.o
clang -S control_flow_showcase.ll -o control_flow_showcase.s
clang ../runtime/main.c control_flow_showcase.o -o control_flow_showcase_app
./control_flow_showcase_app
```

```bash
./mini_cc ../tests/showcase/nested_calls_and_scopes.mc --emit-ir -o nested_calls_and_scopes.o
clang -S nested_calls_and_scopes.ll -o nested_calls_and_scopes.s
clang ../runtime/main.c nested_calls_and_scopes.o -o nested_calls_and_scopes_app
./nested_calls_and_scopes_app
```

```bash
./mini_cc ../tests/showcase/loop_switch_aggregation.mc --emit-ir -o loop_switch_aggregation.o
clang -S loop_switch_aggregation.ll -o loop_switch_aggregation.s
clang ../runtime/main.c loop_switch_aggregation.o -o loop_switch_aggregation_app
./loop_switch_aggregation_app
```

## 15. Как понять, что тесты прошли успешно

Если всё в порядке, `scripts/run_tests.sh` в конце пишет примерно:

```text
Passed: 30
Failed: 0
```

Если написано `Failed: 0`, значит тесты прошли.

## 16. Что делать, если команда не находится

Если, например, система пишет:

```text
command not found: cmake
```

или:

```text
command not found: flex
```

это значит, что зависимость не установлена.

Снова выполните:

```bash
sudo apt update
sudo apt install -y cmake make clang llvm llvm-dev flex bison
```

## 17. Что делать, если проект не собирается

Сначала очистите папку сборки и соберите заново:

```bash
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

Если ошибка остаётся:

- проверьте, что вы запускаете команды именно в Linux/WSL;
- проверьте, что установлены `llvm`, `clang`, `flex`, `bison`;
- проверьте, что проект был полностью скопирован с флешки, а не частично.

## 18. Минимальный набор команд, если нужно просто быстро проверить проект

Из корня проекта:

```bash
sudo apt update
sudo apt install -y cmake make clang llvm llvm-dev flex bison
mkdir -p build
cd build
cmake ..
cmake --build .
./mini_cc ../tests/positive/switch_default.mc --emit-ir -o generated.o
llvm-nm generated.o
clang ../runtime/main.c generated.o -o demo_app
./demo_app
../scripts/run_tests.sh
```

## 19. Если нужно только посмотреть новые showcase-тесты

Из корня проекта:

```bash
./scripts/run_tests.sh
ls -l build/showcase_asm
```

Если нужно посмотреть код этих тестов:

```bash
ls tests/showcase
cat tests/showcase/control_flow_showcase.mc
cat tests/showcase/nested_calls_and_scopes.mc
cat tests/showcase/loop_switch_aggregation.mc
```

## 20. Что читать дальше

Если проект уже запускается и вы хотите понять, как он устроен:

- начните с `README.md`
- затем откройте `compiler_answers.md`

Если хотите смотреть код по этапам:

1. `src/lexer.l`
2. `src/parser.y`
3. `include/ast.hpp`
4. `src/sema.cpp`
5. `src/codegen.cpp`
6. `src/object_emitter.cpp`

