cmake_minimum_required(VERSION 3.19)
project(BombardSim C CXX)

# Standarder
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Konfigurera raylib-inst�llningar ---
set(PLATFORM "Desktop" CACHE STRING "raylib platform" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

# --- 2. H�mta raylib ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# --- 3. Definiera k�llkodsfiler ---
# Detta kommando letar upp ALLA .cpp-filer i mappen s� du slipper skriva dem manuellt
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# --- 4. L�nka beroenden f�r Raspberry Pi 5 ---
if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        raylib 
        GL 
        m 
        pthread 
        dl 
        rt 
        X11
        asound
    )
endif()
if(APPLE)
    # Specifikt för macOS: Länkar in Apples egna grafiksystem
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        raylib 
        "-framework IOKit" 
        "-framework Cocoa" 
        "-framework OpenGL" 
        "-framework CoreVideo"
    )
endif()

# G�r det l�tt att hitta bin�rfilen
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# --- 5. Kopiera Assets till bin-mappen ---
# Detta kommando körs varje gång du skriver 'make'
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "${CMAKE_BINARY_DIR}/bin/assets"
    COMMENT "Kopierar assets till bin-mappen för att Raylib ska hitta dem"
)