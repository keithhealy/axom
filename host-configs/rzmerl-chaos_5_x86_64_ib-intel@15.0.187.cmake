##################################
# uberenv host-config
#
# This is a generated file, edit at own risk.
##################################
# chaos_5_x86_64_ib-intel@15.0.187
##################################

# cmake from uberenv
# cmake executable path: /usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/cmake-3.3.1-hfuoutyx5kxdhsvl6pkw34xatuo6ledt/bin/cmake

#######
# using intel@15.0.187 compiler spec
#######

# c compiler used by spack
set(CMAKE_C_COMPILER "/usr/local/tools/ic-15.0.187/bin/icc" CACHE PATH "")

# cpp compiler used by spack
set(CMAKE_CXX_COMPILER "/usr/local/tools/ic-15.0.187/bin/icpc" CACHE PATH "")

# fortran compiler used by spack
set(ENABLE_FORTRAN ON CACHE PATH "")

set(CMAKE_Fortran_COMPILER  "/usr/local/tools/ic-15.0.187/bin/ifort" CACHE PATH "")

# hdf5 from uberenv
set(HDF5_DIR "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/hdf5-1.8.16-ibq54wdkvnyrbkxedqk5nou77k6aiyet" CACHE PATH "")

# conduit from uberenv
set(CONDUIT_DIR "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/conduit-github-2016-05-18-f3toftwzsd5govlev7nyxpy7hp7w2kh7" CACHE PATH "")

# doxygen from uberenv
set(DOXYGEN_EXECUTABLE "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/doxygen-1.8.11-2irql5puzvwfsqne5wpclbm63ys72pfu/bin/doxygen" CACHE PATH "")

# python from uberenv
set(PYTHON_EXECUTABLE "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/python-2.7.11-q4nixw4uagy2tlyfeto7rhsi5wungimh/bin/python" CACHE PATH "")

# lua from uberenv
set(LUA_DIR "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/lua-5.1.5-rfr5m5nbtre7gkouhvst6waau6mi5qvl" CACHE PATH "")

# sphinx from uberenv
set(SPHINX_EXECUTABLE "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/python-2.7.11-q4nixw4uagy2tlyfeto7rhsi5wungimh/bin/sphinx-build" CACHE PATH "")

# uncrustify from uberenv
set(UNCRUSTIFY_EXECUTABLE "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/uncrustify-0.61-onqgsfbevtniuj45s564dpfkmlveql33/bin/uncrustify" CACHE PATH "")

# sparsehash headers from uberenv
set(SPARSEHASH_DIR "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/sparsehash-headers-2.0.2-4q2ms4ib3yes7y7hrekj5zigrrzh3qhp" CACHE PATH "")

# boost headers from uberenv
set(ENABLE_BOOST ON CACHE PATH "")
set(BOOST_ROOT "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/boost-headers-1.58.0-m4zq524o33mi34qimoxtn5rae4amyk6w" CACHE PATH "")

# lcov and genhtml from uberenv
set(LCOV_PATH "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/lcov-1.11-hyyvo3em3ckyvwg5bz27koz2ulmsbms3/usr/bin/lcov" CACHE PATH "")

set(GENHTML_PATH "/usr/workspace/wsrzc/toolkit/thirdparty_libs/builds/2016_05_25_17_18_11/spack/opt/spack/chaos_5_x86_64_ib/intel-15.0.187/lcov-1.11-hyyvo3em3ckyvwg5bz27koz2ulmsbms3/usr/bin/genhtml" CACHE PATH "")

# Temporarily disable CXX11 on intel builds until we resolve issue ATK-619
set(ENABLE_CXX11 OFF CACHE PATH "")
##################################
# end uberenv host-config
##################################

##############################################################################
# !---------------------------------------------------------------------------
##############################################################################
# Options added manually to 
# lc chaos5 intel@15.0.187 host configs
##############################################################################

##############################################################################
# MPI - manually added for now
##############################################################################
set(ENABLE_MPI ON CACHE PATH "")
set(MPI_C_COMPILER "/usr/local/tools/mvapich2-intel-2.0/bin/mpicc" CACHE PATH "")
set(MPI_CXX_COMPILER "/usr/local/tools/mvapich2-intel-2.0/bin/mpicxx" CACHE PATH "")
set(MPI_Fortran_COMPILER  "/usr/local/tools/mvapich2-intel-2.0/bin/mpif90" CACHE PATH "")

##############################################################################
# !---------------------------------------------------------------------------
##############################################################################
