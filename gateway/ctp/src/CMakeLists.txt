

ADD_DEFINITIONS(-DDEBUG)
set(ctp_gateway_src error_handle.cpp md_spi.cpp struct_build.cpp trader_spi.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs)
add_library(ctpgw SHARED ${ctp_gateway_src})
target_link_libraries(ctpgw pthread configparser thostmduserapi thosttraderapi )