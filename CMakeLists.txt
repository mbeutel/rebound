
# CMake build script for REBOUND


cmake_minimum_required(VERSION 3.20)

project(rebound
    VERSION 3.18.0
    LANGUAGES C
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Define build options.
option(ENABLE_MPI "Compile with MPI support" OFF)
option(ENABLE_OPENGL "Compile with OpenGL support" OFF)
option(ENABLE_QUADRUPOLE "TODO" OFF)
option(ENABLE_PROFILING "Enable profiling" OFF)
option(USE_FFTW "Use FFTW" OFF)

# Include target definitions.
add_subdirectory(src)

# Install.
include(InstallBasicPackageFiles)
cmakeshift_install_basic_package_files(rebound
    COMPATIBILITY SameMajorVersion
    DEPENDENCIES
        "Threads"
)
