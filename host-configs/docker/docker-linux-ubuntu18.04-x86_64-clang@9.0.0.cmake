#------------------------------------------------------------------------------
# !!!! This is a generated file, edit at own risk !!!!
#------------------------------------------------------------------------------
# SYS_TYPE: linux-ubuntu18.04-skylake
# Compiler Spec: clang@9.0.0
#------------------------------------------------------------------------------
# CMake executable path: /home/axom/axom_tpls/clang-9.0.0/cmake-3.10.1/bin/cmake
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Compilers
#------------------------------------------------------------------------------

set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE PATH "")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE PATH "")

set(ENABLE_FORTRAN ON CACHE BOOL "")

set(CMAKE_Fortran_COMPILER "/usr/bin/gfortran" CACHE PATH "")

set(CMAKE_CXX_FLAGS "-stdlib=libc++" CACHE PATH "")

set(BLT_EXE_LINKER_FLAGS " -Wl,-rpath,/usr/lib" CACHE PATH "Adds a missing libstdc++ rpath")

#------------------------------------------------------------------------------
# TPLs
#------------------------------------------------------------------------------

# Root directory for generated TPLs
set(TPL_ROOT "/home/axom/axom_tpls/clang-9.0.0" CACHE PATH "")

set(CONDUIT_DIR "${TPL_ROOT}/conduit-0.5.1" CACHE PATH "")

# MFEM not built

set(HDF5_DIR "${TPL_ROOT}/hdf5-1.8.21" CACHE PATH "")

set(LUA_DIR "${TPL_ROOT}/lua-5.3.5" CACHE PATH "")

# SCR not built

set(RAJA_DIR "${TPL_ROOT}/raja-0.12.1" CACHE PATH "")

set(UMPIRE_DIR "${TPL_ROOT}/umpire-4.0.1" CACHE PATH "")

#------------------------------------------------------------------------------
# MPI
#------------------------------------------------------------------------------

set(ENABLE_MPI ON CACHE BOOL "")

set(MPI_C_COMPILER "/home/axom/axom_tpls/clang-9.0.0/mpich-3.0.3/bin/mpicc" CACHE PATH "")

set(MPI_CXX_COMPILER "/home/axom/axom_tpls/clang-9.0.0/mpich-3.0.3/bin/mpic++" CACHE PATH "")

set(MPI_Fortran_COMPILER "/home/axom/axom_tpls/clang-9.0.0/mpich-3.0.3/bin/mpif90" CACHE PATH "")

set(MPIEXEC_EXECUTABLE "/home/axom/axom_tpls/clang-9.0.0/mpich-3.0.3/bin/mpirun" CACHE PATH "")

set(MPIEXEC_NUMPROC_FLAG "-np" CACHE PATH "")

#------------------------------------------------------------------------------
# Devtools
#------------------------------------------------------------------------------

set(ENABLE_DOCS OFF CACHE BOOL "")

# Unable to find clang-format

#------------------------------------------------------------------------------
# Other machine specifics
#------------------------------------------------------------------------------

set(ENABLE_OPENMP ON CACHE BOOL "")

set(ENABLE_GTEST_DEATH_TESTS ON CACHE BOOL "")
