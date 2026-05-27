# Mini Compiler Course Project

Учебный мини-компилятор на C++17, Flex, GNU Bison и LLVM для `x86_64 Linux`.

Проект компилирует упрощённый Rust-like язык в LLVM IR и объектный файл `.o`, который затем можно слинковать с внешним `main.c`.

## Вариант

- Архитектура: `x86 / x86_64 Linux`
- Target triple по умолчанию: `x86_64-pc-linux-gnu`
- Дополнительная конструкция: `switch / case / default`
- Синтаксис: Rust-like
- Лексер: Flex
- Парсер: GNU Bison
- Backend: LLVM IR -> object file

## Поддержанные возможности языка

- Типы: `int`, `bool`
- Функции и вызовы функций
- Локальные переменные: `let` и `let mut`
- Присваивание
- Блочная область видимости
- Арифметика: `+`, `-`, `*`, `/`, `%`
- Сравнения: `==`, `!=`, `<`, `<=`, `>`, `>=`
- Логика: `&&`, `||`, `!`
- `if / else`
- `for`
- `return`
- `switch / case / default`
- `break` в `switch` и циклах
- `continue` в циклах

## Ограничения

- `float` не реализован, чтобы сохранить компактность и стабильность курсового проекта.
- Тип `int` реализован как LLVM `i64`.
- Тип `bool` реализован как LLVM `i1`.
- Поддержан один стабильный синтаксис цикла:

```rust
for let mut i: int = 0; i < 10; i = i + 1 {
    // body
}
```

- `switch` работает без fallthrough: после каждого `case` управление завершается `return`, `break` или неявным переходом в `switch.end`.

## Зависимости

Нужны установленные инструменты:

- `cmake`
- `make`
- `clang`
- `llvm-config`
- `llvm-nm`
- `flex`
- `bison`

Для Ubuntu/WSL обычно подходят пакеты:

```bash
sudo apt install cmake make clang llvm-dev llvm flex bison
```

## Сборка

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

После сборки исполняемый файл компилятора находится по пути `build/mini_cc`.

## Использование компилятора

Базовый запуск:

```bash
./mini_cc ../tests/positive/switch_default.mc -o generated.o
```

Сохранить LLVM IR рядом с объектным файлом:

```bash
./mini_cc ../tests/positive/switch_default.mc --emit-ir -o generated.o
```

В этом случае рядом будет создан файл `generated.ll`.

Задать target triple:

```bash
./mini_cc ../tests/positive/switch_default.mc --target x86_64-pc-linux-gnu -o generated.o
```

## Контракт с runtime

Программа на учебном языке должна экспортировать функцию:

```c
extern int64_t compiled_fn(int64_t arg);
```

LLVM-функция генерируется как:

```llvm
define i64 @compiled_fn(i64 %arg)
```

## Линковка с main.c

Проверка символа:

```bash
llvm-nm generated.o
```

Линковка:

```bash
clang ../runtime/main.c generated.o -o demo_app
```

Запуск:

```bash
./demo_app
```

## Примеры синтаксиса

```rust
fn compiled_fn(arg: int) -> int {
    let mut x: int = arg;

    if x > 10 {
        x = x * 2;
    } else {
        x = x + 1;
    }

    switch x {
        case 0 {
            return 100;
        }
        case 1 {
            return 101;
        }
        default {
            return x;
        }
    }
}
```

```rust
fn compiled_fn(arg: int) -> int {
    let mut sum: int = 0;

    for let mut i: int = 0; i < arg; i = i + 1 {
        sum = sum + i;
    }

    return sum;
}
```

## Тесты

Из корня проекта:

```bash
./scripts/run_tests.sh
```

Из каталога `build`:

```bash
../scripts/run_tests.sh
```

Скрипт:

- пересобирает проект;
- компилирует все позитивные тесты;
- проверяет наличие символа `compiled_fn`;
- линкует объектный файл с `runtime/main.c`;
- запускает итоговый executable;
- проверяет ожидаемый `stdout`;
- проверяет, что негативные тесты завершаются ошибкой и содержат понятную диагностику.

## Структура проекта

- `src/lexer.l` — Flex-лексер
- `src/parser.y` — Bison-грамматика
- `include/ast.hpp`, `src/ast.cpp` — AST
- `include/sema.hpp`, `src/sema.cpp` — семантический анализ
- `include/codegen.hpp`, `src/codegen.cpp` — генерация LLVM IR
- `include/object_emitter.hpp`, `src/object_emitter.cpp` — выпуск `.o`
- `src/driver.cpp` — CLI-драйвер
- `runtime/main.c` — внешний runtime для линковки
- `tests/` — позитивные и негативные интеграционные тесты
- `scripts/run_tests.sh` — автоматический тестовый прогон
- `compiler_answers.md` — подробные ответы по теории и архитектуре проекта
