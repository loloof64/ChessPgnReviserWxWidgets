cmake_minimum_required(VERSION 3.0)

project(ChessPgnReviser VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_DEFINITIONS(-Wall -Wno-sign-compare -O2)

# https://stackoverflow.com/a/27206982/662618 (Creative Commons  BY-SA 3.0)
# Creates C resources file from files in given directory
function(create_resources dir output)
    # Create empty output file
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()

create_resources(
    src/gui/chess_board/pieces_images
    src/gui/chess_board/pieces_resources.c
)

set(SRCS
    src/main.cpp
    src/gui/chess_board/chessboard.cpp
    src/gui/chess_board/ThcPosition.cpp
    src/gui/chess_board/pieces_resources.c
    src/gui/chess_board/promotiondialog.cpp
    src/gui/main_window.cpp
    src/libs/thc-chess-library/ChessPosition.cpp
    src/libs/thc-chess-library/ChessRules.cpp
    src/libs/thc-chess-library/Move.cpp
    src/libs/thc-chess-library/PrivateChessDefs.cpp
    src/libs/thc-chess-library/util.cpp
)

set(HEADERS
    src/gui/chess_board/chessboard.h
    src/gui/chess_board/IPosition.h
    src/gui/chess_board/ThcPosition.h
    src/gui/chess_board/nanosvg.h
    src/gui/chess_board/nanosvgrast.h
    src/gui/chess_board/promotiondialog.h
    src/gui/main_window.h
    src/libs/thc-chess-library/ChessDefs.h
    src/libs/thc-chess-library/ChessPosition.h
    src/libs/thc-chess-library/ChessPositionRaw.h
    src/libs/thc-chess-library/ChessRules.h
    src/libs/thc-chess-library/DebugPrintf.h
    src/libs/thc-chess-library/GeneratedLookupTables.h
    src/libs/thc-chess-library/HashLookup.h
    src/libs/thc-chess-library/Move.h
    src/libs/thc-chess-library/PrivateChessDefs.h
    src/libs/thc-chess-library/util.h
)

add_executable(ChessPgnReviser ${SRCS} ${HEADERS})

find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  target_link_libraries(ChessPgnReviser ${wxWidgets_LIBRARIES})
else()
    message(FATAL_ERROR "Failed to find WxWidgets library")
endif()