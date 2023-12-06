cmake_minimum_required (VERSION 3.8)

project ("FSM")
file(GLOB 
		HPPS "src/*.h" "src/FSM_CLASS/*.h" "src/FIND_STRING/*.h" 
		CPPS "src/*.cpp" "src/FSM_CLASS/*.cpp" "src/FIND_STRING/*.cpp" )


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/test.txt
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

add_executable (${PROJECT_NAME} ${CPPS} ${HPPS})
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FSM PROPERTY CXX_STANDARD 20)
endif()
