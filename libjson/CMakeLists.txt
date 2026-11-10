# CMakeList.txt : CMake project for json, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (libjson
	"boolean.cpp"
	"data.cpp"
	"null.cpp"
	"number.cpp"
	"string.cpp"
	"var.cpp"
	"array.cpp"
	"object.cpp")

target_include_directories(libjson PUBLIC ".")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libjson PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
