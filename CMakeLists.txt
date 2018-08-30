cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-m64)

project(ctp)

set(CTP_INC_DIR third-party-libs/ctp/include)
set(CTP_LINK_DIR third-party-libs/ctp/libs)

include_directories(${CTP_INC_DIR})
include_directories(/usr/local/boost_1_66_0)
include_directories(include)
link_directories(${CTP_LINK_DIR})

add_subdirectory(third-party-libs/pybind11)

add_library(ctp MODULE src/main.cpp src/market_service.cpp src/data_convertor.cpp src/trader_service.cpp)
# target_link_libraries(CTPBind PRIVATE pybind11::module)
target_link_libraries(ctp PRIVATE pybind11::module PUBLIC thostmduserapi thosttraderapi boost_locale)
# target_link_libraries(CTPBind thosttraderapi)
set_target_properties(ctp PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")

