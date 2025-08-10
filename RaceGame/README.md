# Курсовой проект «Симулятор гонок» (реализация)

Реализация по заданию Нетологии из репозитория `netology-code/cppm-diplom`.  
Структура соответствует требованиям: классы ТС и гонок вынесены в динамическую библиотеку, взаимодействие с пользователем — в `app/main.cpp`.

## Сборка (CMake)

```
git clone <this-zip-unpacked-folder>
cd cppm-diplom-racing
cmake -S . -B build
cmake --build build --config Release
```

Запуск:
- Windows: `build/Release/racing_app.exe` (или `build/racing_app.exe` для MinGW)
- Linux/macOS: `./build/racing_app`

## Замечания по реализации
- Транспорт и гонки организованы в виде иерархий классов (`Vehicle`, `LandVehicle`, `AirVehicle`, конкретные ТС).
- Время для наземных ТС считается с учётом пауз отдыха по правилам задания.
- Для воздушных ТС применяется коэффициент сокращения дистанции согласно заданию.
- Библиотека собирается как `SHARED` и использует экспорт `RACING_API` для Windows.


## Visual Studio 2022 (MSVC v143)
Способ 1 — через CMakePresets:
1. Откройте папку проекта в VS 2022 (**File → Open → Folder…**).
2. Выберите пресет `vs2022-x64` и конфигурацию `Release`/`Debug`.
3. Запускайте таргет `racing_app` — DLL автоматически будет скопирована рядом с EXE.

Способ 2 — генерация .sln из терминала (x64 Native Tools for VS 2022):
```bat
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -T v143
cmake --build build --config Release
```
