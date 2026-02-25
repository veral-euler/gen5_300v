# ==============================================================================
#  cmake/arm-none-eabi.cmake
#  ARM Cortex-M bare-metal toolchain file for CMake
#  Place this file at: <your_project>/cmake/arm-none-eabi.cmake
# ==============================================================================

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# --- Toolchain prefix ---------------------------------------------------------
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# --- Compiler executables -----------------------------------------------------
#  If arm-none-eabi-gcc is NOT on your PATH, set the full path here:
#  e.g. set(TC "/opt/arm-gnu-toolchain/bin/")
set(TC "")

set(CMAKE_C_COMPILER       ${TC}${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER     ${TC}${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER     ${TC}${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_AR               ${TC}${TOOLCHAIN_PREFIX}ar)
set(CMAKE_LINKER           ${TC}${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY          ${TC}${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP          ${TC}${TOOLCHAIN_PREFIX}objdump)
set(CMAKE_SIZE             ${TC}${TOOLCHAIN_PREFIX}size)
set(CMAKE_STRIP            ${TC}${TOOLCHAIN_PREFIX}strip)

# --- Prevent CMake from testing the compiler with a host-linked binary --------
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# --- Sysroot / search paths ---------------------------------------------------
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # Use host tools (cmake, python…)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)    # Only look in sysroot for libs
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)    # Only look in sysroot for headers
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

