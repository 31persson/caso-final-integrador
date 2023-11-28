cmake_minimum_required(VERSION 3.12)
project(caso_final_integrador)

# Agrega la subcarpeta json11 al proyecto
add_subdirectory(json11)

# Configura tu ejecutable
add_executable(ejercicio ejercicio.cpp)

# Enlaza tu ejecutable con la biblioteca json11
target_link_libraries(ejercicio json11)

# Imprime información
message("C++ Compiler: ${CMAKE_CXX_COMPILER}")
message("Source files: ${CMAKE_SOURCE_DIR}")
message("Binary files: ${CMAKE_BINARY_DIR}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
cmake_minimum_required(VERSION 3.20)
project(caso_final_integrador)

set(CMAKE_CXX_STANDARD 11)

add_executable(ejercicio ejercicio.cpp json11/json11.cpp)  # Añade json11.cpp aquí

# Asegúrate de que estás enlazando correctamente con las bibliotecas necesarias
target_link_libraries(ejercicio)
