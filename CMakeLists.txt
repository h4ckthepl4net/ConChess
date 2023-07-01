# CMakeList.txt : CMake project for ConChess, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ConChess")

# Add source to this project's executable.
add_executable (
	ConChess
	
	"ConChess.cpp"
	"ConChess.h"

	"headers/utilities/Color.h"
	"headers/utilities/Coords.h"
	"headers/utilities/ConsoleEvent.h"
	"headers/utilities/ConsoleEventType.h" 
	"headers/utilities/ClickData.h" 
	"headers/utilities/ConsoleEventDataUnion.h" 
	"headers/utilities/KeyData.h"
	"headers/constants/Pieces.h"
	"headers/constants/PieceIDs.h"
	"headers/constants/FieldDeltas.h"
	"headers/constants/Fields.h"

	"headers/Game.h"
	"headers/Player.h"
	"headers/Board.h"
	"headers/Console.h"
	"headers/Piece.h"
	"headers/special-pieces/King.h"
	"headers/special-pieces/Queen.h"
	"headers/special-pieces/Bishop.h"
	"headers/special-pieces/Knight.h"
	"headers/special-pieces/Rook.h"
	"headers/special-pieces/Pawn.h"
	
	
	"classes/Game.cpp"
	"classes/Player.cpp" 
	"classes/Board.cpp"
	"classes/Console.cpp"
	"classes/Piece.cpp"
	"classes/special-pieces/King.cpp"
	"classes/special-pieces/Queen.cpp"
	"classes/special-pieces/Bishop.cpp"
	"classes/special-pieces/Knight.cpp"
	"classes/special-pieces/Rook.cpp"
	"classes/special-pieces/Pawn.cpp"
	
 "headers/utilities/PlayerStats.h" "headers/Slot.h" "classes/Slot.cpp" "headers/constants/PiecePoints.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ConChess PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
