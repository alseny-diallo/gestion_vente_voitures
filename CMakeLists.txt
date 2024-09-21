cmake_minimum_required(VERSION 3.15)
project(gestion_vente_voitures)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Utiliser mysql_config pour configurer les chemins
execute_process(COMMAND mysql_config --cflags OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(${MYSQL_CFLAGS})
link_directories(${MYSQL_LIBS})

# Ajouter l'exécutable
add_executable(gestion_vente_voitures main.cpp)

# Lier les bibliothèques MySQL
target_link_libraries(gestion_vente_voitures ${MYSQL_LIBS} mysqlcppconn)
