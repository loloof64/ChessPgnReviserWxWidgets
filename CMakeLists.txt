cmake_minimum_required(VERSION 3.0)

project(ChessPgnReviser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_DEFINITIONS(-Wall -Wno-sign-compare -O2)

set(SRCS
    src/main.cpp
    src/chess_board/chessboard.cpp
)

set(HEADERS
    src/chess_board/chessboard.h
)

add_executable(ChessPgnReviser ${SRCS} ${HEADERS})

find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  target_link_libraries(ChessPgnReviser ${wxWidgets_LIBRARIES})
else()
    message(FATAL_ERROR "Failed to find WxWidgets library")
endif()