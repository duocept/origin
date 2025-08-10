add_library(racing_lib SHARED
    src/Vehicle.cpp
    src/LandVehicle.cpp
    src/AirVehicle.cpp
    src/Camel.cpp
    src/CamelFast.cpp
    src/Centaur.cpp
    src/AllTerrainBoots.cpp
    src/Carpet.cpp
    src/Eagle.cpp
    src/Broom.cpp
    src/Race.cpp
)

target_include_directories(racing_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(racing_lib PRIVATE RACING_BUILD)

# For Windows DLL export of classes
if(MSVC)
  target_compile_definitions(racing_lib PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()
