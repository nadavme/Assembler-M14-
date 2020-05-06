cmake_minimum_required(VERSION 3.14.5)
project(Maabada-Mmn14 C)

set(CMAKE_C_STANDARD 90)

add_executable(Maabada-Mmn14 main.c symbolsTable.c aidTools.c memoryMap.c filesAssembler.c
        permanentTables.c secondRunOver.c)