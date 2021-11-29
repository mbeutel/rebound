
# CMake build script for REBOUND
# Shared library target


cmake_minimum_required(VERSION 3.20)

# dependencies
find_package(Threads REQUIRED)
if(ENABLE_MPI)
    find_package(MPI REQUIRED)
endif()
if(ENABLE_OPENMP)
    find_package(OpenMP REQUIRED)
endif()
if(ENABLE_OPENGL)
    find_package(glfw3 REQUIRED)
endif()
if(WIN32)
    find_package(pthreads REQUIRED)
endif()

# library target
add_library(rebound SHARED  # `SHARED` implies position-independent code on platforms that need it
    "binarydiff.c"
    "boundary.c"
    "collision.c"
    "communication_mpi.c"
    "derivatives.c"
    "display.c"
    "glad.c"
    "gravity.c"
    "input.c"
    "integrator.c"
    "integrator_eos.c"
    "integrator_ias15.c"
    "integrator_janus.c"
    "integrator_leapfrog.c"
    "integrator_mercurius.c"
    "integrator_saba.c"
    "integrator_sei.c"
    "integrator_whfast.c"
    "output.c"
    "particle.c"
    "rebound.c"
    "simulationarchive.c"
    "tools.c"
    "transformations.c"
    "tree.c"
    "posix_polyfill.c"

    # list of shared library exports (required on Windows)
    "rebound.def"
    "$<$<BOOL:${ENABLE_MPI}>:rebound-MPI.def>"
    "$<$<BOOL:${ENABLE_OPENMP}>:rebound-OpenMP.def>"
)

# library properties and dependencies
target_compile_definitions(rebound
    PUBLIC
        $<$<BOOL:${ENABLE_MPI}>:MPI>
        $<$<BOOL:${ENABLE_OPENMP}>:OPENMP>
        #"GITHASH=${GIT_HASH}"  # TODO
    PRIVATE
        LIBREBOUND
        $<$<BOOL:${ENABLE_OPENGL}>:OPENGL>
        $<$<BOOL:${ENABLE_QUADRUPOLE}>:QUADRUPOLE>
        $<$<BOOL:${ENABLE_PROFILING}>:PROFILING>
)
target_link_libraries(rebound
    PUBLIC
        Threads::Threads  # link `pthread` and `rt` on platforms that need it
        $<$<PLATFORM_ID:Windows>:PThreads4W::PThreads4W>  # link Pthreads for Win32 on Windows
        $<$<BOOL:${ENABLE_MPI}>:MPI::MPI_C>
        $<$<BOOL:${ENABLE_OPENMP}>:OpenMP::OpenMP_C>
    PRIVATE
        $<$<C_COMPILER_ID:GNU>:m>  # link libstdc++ math library ("m") when compiling with GCC
        $<$<BOOL:${ENABLE_OPENGL}>:glfw>
)
target_include_directories(rebound
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
        "$<INSTALL_INTERFACE:include>"
)
target_compile_features(rebound
    PUBLIC
        c_std_11
)
include(TargetCompileSettings)
cmakeshift_target_compile_settings(rebound)

# installation: public header file, target
install(
    FILES rebound.h
    TYPE INCLUDE
)
install(
    TARGETS rebound
    EXPORT rebound
    ARCHIVE LIBRARY RUNTIME
)
