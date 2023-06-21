# Minimum version of cmake required for compiling or project (I recommended at least cmake v 2.8.12, better v 3)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# The name of the project, we will use "Dose" for the G4 dose calculation applications
project(G4Dose)

# Let's tell cmake what packages we required or need (not the same!)
# No UI or VIS, uncomment this and comment the other one
# find_package(Geant4 REQUIRED)
find_package(Geant4 REQUIRED ui_all vis_all)

# Include G4 libraries. ${string} are environmental variables
include(${Geant4_USE_FILE})

# Locate sources and headers 
# ${PROJECT_SOURCE_DIR} is the directory where CMakeLists.txt is located (${PWD})

include_directories(${PROJECT_SOURCE_DIR}/inc
                    ${Geant4_INCLUDE_DIR})
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/*.hh)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

# The name of the excecutable we will use, and the files that will be linked to it
# dose is the excecutable, dose.cc the main source, etc
add_executable(dose dose.cc ${sources} ${headers})

# The Geant4 libraries that will be linked to our excecutable...
target_link_libraries(dose ${Geant4_LIBRARIES})

# Linking the excecutable with our project
add_custom_target(G4Dose DEPENDS dose)
