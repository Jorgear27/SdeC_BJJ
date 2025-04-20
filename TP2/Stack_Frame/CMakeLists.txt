cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(CalculadorASM)

# Configuración del ensamblador NASM
set(ASM_SOURCE c_assembler/operaciones.asm)
set(ASM_OBJECT operaciones.o)

# Configuración del archivo fuente en C
set(C_SOURCE c_assembler/main.c)

# Comando para compilar el archivo ASM con NASM
add_custom_command(
    OUTPUT ${ASM_OBJECT}
    COMMAND nasm -f elf64 ${CMAKE_SOURCE_DIR}/${ASM_SOURCE} -o ${CMAKE_BINARY_DIR}/${ASM_OBJECT}
    DEPENDS ${ASM_SOURCE}
    COMMENT "Compilando ${ASM_SOURCE} con NASM"
)

# Agregar el archivo ensamblado como un objeto
add_custom_target(CompileASM ALL DEPENDS ${ASM_OBJECT})

# Crear el ejecutable final
add_executable(calcular ${C_SOURCE} ${CMAKE_BINARY_DIR}/${ASM_OBJECT})

# Configurar opciones de compilación para GCC
target_link_options(calcular PRIVATE -no-pie)

# Asegurar que el ensamblado se realice antes de compilar el ejecutable
add_dependencies(calcular CompileASM)