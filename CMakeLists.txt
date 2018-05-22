cmake_minimum_required(VERSION 3.9)
project(bt)
set(CMAKE_CXX_STANDARD 11)



#include_directories(/opt/Ice-3.7.0/include/) is use ice
#add_definitions(-DUSEICE)// if use ice broadcast
add_compile_options(-DICE_CPP11_MAPPING)
add_subdirectory(dataApi)
add_subdirectory(config_parse)
add_subdirectory(gateway/ctp)

ADD_DEFINITIONS(-DDEBUG)
include_directories(${PROJECT_SOURCE_DIR}/gateway/ctp/include)


#add_executable(testmain testmain.cpp gateway/ctp/src/md_spi.cpp gateway/ctp/src/error_handle.cpp gateway/ctp/src/trader_spi.cpp gateway/ctp/src/struct_build.cpp eventApi/EventBus.cpp)
add_executable(testmain testmain.cpp eventApi/EventBus.cpp longfirst/LFConstants.h longfirst/LFDataStruct.h longfirst/LFPrintUtils.h longfirst/ctp.h longfirst/LFUtils.h longfirst/sysmessages.h longfirst/transfer_m.h longfirst/xtp.h events/L1TickEvent_LF.h events/OrderEvent_LF.h events/TradeEvent_LF.h)

#link_directories("${PROJECT_SOURCE_DIR}/gateway/ctp/libs")
message(${PROJECT_SOURCE_DIR}/gateway/ctp/libs)
#target_link_libraries(testmain pthread configparser libthostmduserapi.so libthosttraderapi.so)
target_link_libraries(testmain pthread configparser ctpgw /home/liulongxiao/CLionProjects/bt/gateway/ctp/libs/libthostmduserapi.so /home/liulongxiao/CLionProjects/bt/gateway/ctp/libs/libthosttraderapi.so)


