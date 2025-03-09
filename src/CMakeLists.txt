# CMakeList.txt : CMake project for Resolver, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Resolver "main.cpp"  "Resolver.h" "Resolver.cpp" "MathElement.h" "MathElement.cpp" "MathObject.h" "MathObject.cpp" "IResolvable.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Resolver PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
