###############################################################################
## Action #9
cmake_minimum_required(VERSION 3.17.0) # version can be different

###############################################################################
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-g -O0 -std=c++11 -stdlib=libc++ -U__STRICT_ANSI__ -fprofile-instr-generate -fcoverage-mapping")

###############################################################################
project(WordsExampleSpring2022) 

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>
include_directories(include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

###############################################################################
add_executable(tests) 
target_include_directories(tests PUBLIC model)
target_sources(tests PUBLIC 
   model/StoredString.cpp
   model/StoredString.h
   tests/tests.cpp)
target_link_libraries(tests PRIVATE gtest) # link google test to this executable
set_property(TARGET tests PROPERTY CXX_STANDARD 11)

###############################################################################
add_custom_target(coverage
    COMMAND tests
    COMMAND llvm-profdata merge -sparse default.profraw -o cumulative.profdata
    COMMAND llvm-cov show -ignore-filename-regex='../google*/*' -format="html" ./tests -instr-profile=cumulative.profdata > coverageLines.html
    COMMAND llvm-cov report -show-region-summary=false -ignore-filename-regex='../google*/*'  ./tests -instr-profile=cumulative.profdata > coverageSummary.txt
    COMMAND cat coverageSummary.txt
)
add_dependencies(coverage tests)

enable_testing()
include(GoogleTest)
gtest_discover_tests(tests)

###############################################################################
#Add target to build documents 
set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
#set the output directory of the documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)
# sanity check...
message("Doxygen Output ${DOXYGEN_OUTPUT_DIR}")
find_package(Doxygen)

###############################################################################
if(DOXYGEN_FOUND)
    # create the output directory where the documentation will live
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
    # configure our Doxygen configuration file. This will be the input to the doxygen
    # executable
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

   # now add the custom target. This will create a build target called 'document' 
   # in your project
   ADD_CUSTOM_TARGET(document
   COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
   COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
   COMMAND ${CMAKE_COMMAND} -E echo "Done."
   WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

endif(DOXYGEN_FOUND)

###############################################################################
#Add target to format code 
if(NOT CLANG_FORMAT)
    find_program(CLANG_FORMAT "clang-format")
endif()
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_CXX_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/model/*.cpp
        ${PROJECT_SOURCE_DIR}/model/*.h
        ${PROJECT_SOURCE_DIR}/model/*.hpp
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
    )

    add_custom_target(
        ${PROJECT_NAME}_format
        COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES}
    )

    if(NOT TARGET format)
        add_custom_target(format)
    endif()

    add_dependencies(format ${PROJECT_NAME}_format)
endif()

add_dependencies(format tests)
