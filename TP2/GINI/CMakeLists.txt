cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(CalculadoraGINI LANGUAGES C)

# Configuración del ensamblador NASM
set(ASM_SOURCE c_assembler/gini_ops.asm)
set(ASM_OBJECT gini_ops.o)

# Configuración del archivo fuente en C
set(C_SOURCE c_assembler/calcular_gini.c)
set(C_OBJECT calcular_gini.o)

# Comando para compilar el archivo ASM con NASM en modo DEBUG
add_custom_command(
    OUTPUT ${ASM_OBJECT}
    COMMAND nasm -f elf64 -g -F dwarf ${CMAKE_SOURCE_DIR}/${ASM_SOURCE} -o ${CMAKE_BINARY_DIR}/${ASM_OBJECT}
    DEPENDS ${ASM_SOURCE}
    COMMENT "Compilando ${ASM_SOURCE} con NASM en modo DEBUG"
)

# Comando para compilar el archivo C en modo DEBUG
add_custom_command(
    OUTPUT ${C_OBJECT}
    COMMAND gcc -g -c ${CMAKE_SOURCE_DIR}/${C_SOURCE} -o ${CMAKE_BINARY_DIR}/${C_OBJECT}
    DEPENDS ${C_SOURCE}
    COMMENT "Compilando ${C_SOURCE} con GCC en modo DEBUG"
)

# Agregar los archivos ensamblados y compilados como objetivos
add_custom_target(CompileASM ALL DEPENDS ${ASM_OBJECT})
add_custom_target(CompileC ALL DEPENDS ${C_OBJECT})

# Crear el ejecutable final en modo DEBUG
add_executable(calcular_gini ${CMAKE_BINARY_DIR}/${C_OBJECT} ${CMAKE_BINARY_DIR}/${ASM_OBJECT})

# Configurar opciones de compilación para GCC
set_target_properties(calcular_gini PROPERTIES LINKER_LANGUAGE C)
target_link_options(calcular_gini PRIVATE -g -no-pie -lm)

# Asegurar que el ensamblado y la compilación se realicen antes de crear el ejecutable
add_dependencies(calcular_gini CompileASM CompileC)