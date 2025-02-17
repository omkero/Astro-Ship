cmake_minimum_required(VERSION 3.14)
project(astro_ship)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(SDL2_STATIC ON)
set(SDL2_LIBRARIES ${SDL2_LIBRARY} SDL2main SDL2-static SDL2_ttf-static)

# Add executable binaries (.cpp files)
add_executable(${PROJECT_NAME} 
    main.cpp 
    ui/Button.cpp 
    ui/Text.cpp 
    ui/Display.cpp
    objects/Sprite.cpp
    objects/enemy/astroids.cpp
    objects/Shapes/CircleRectShape.cpp
    objects/Shapes/RectangleShape.cpp
    objects/player2D/Player2D.cpp
    core/window/Window.cpp
    core/renderer/Renderer.cpp
    core/physics/detections.cpp
    maps/SpaceBackground.cpp
)

# On Linux, ensure SDL2 is found
if(NOT WIN32)
    find_package(SDL2 REQUIRED)
   # find_package(OpenGL REQUIRED)
endif()

# Link SDL2 and other libraries
if(WIN32)
    # On Windows, set the resource files
    set(RESOURCE_FILES ${CMAKE_SOURCE_DIR}/icon.rc)

    # Link libraries for Windows
    target_link_libraries(${PROJECT_NAME} 
        ${CMAKE_SOURCE_DIR}/lib/x64/SDL2-static.lib  # Explicitly link SDL2 static library
        ${CMAKE_SOURCE_DIR}/lib/x64/SDL2main.lib     # Include SDL2main for static linking
        ${CMAKE_SOURCE_DIR}/lib/x64/SDL2_image.lib     # Include SDL2main for static linking
        ${CMAKE_SOURCE_DIR}/lib/x64/SDL2_ttf.lib     # Include SDL2main for static linking
        ${CMAKE_SOURCE_DIR}/lib/x64/glew32.lib
        ${CMAKE_SOURCE_DIR}/lib/x64/SDL2_mixer.lib
        winmm                       # Windows Multimedia API
        imm32                       # Input Method Manager
        version                     # Version API
        setupapi                    # SetupAPI library for device functions
        cfgmgr32                    # CfgMgr32 library for device functions
        user32                      # User32 library for window management
        kernel32
        opengl32                    # Kernel32 library for basic application functionality
    )

    # Set WIN32 flag for GUI app (to prevent console)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE   # Ensure it's treated as a GUI app
    )

    # Ensure that SDL2 is linked statically
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS  "-static -static-libgcc -static-libstdc++"
    )

else()  # If not Windows, assume it's Linux

    # Link libraries for Linux
    target_link_libraries(${PROJECT_NAME} 
        SDL2      # Link SDL2 (find_package should already handle this)
        SDL2main  # Link SDL2main
        SDL2_image
        SDL2_mixer
        SDL2_ttf        # Link SDL2_ttf (ensure you have the appropriate SDL2_ttf package installed)
      # OpenGL::GL      # Link OpenGL (find_package should handle this)   # Link GLEW if you're using it (you may need to adjust based on how GLEW is set up)
        m                # Link math library
    )
    
    # For Linux, we ensure the math library is linked
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        SDL_MAIN_HANDLED
        SDL_STATIC
    )

endif()

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    SDL_MAIN_HANDLED
    SDL_STATIC
)

if(WIN32)
    set(RESOURCE_FILES ${CMAKE_SOURCE_DIR}/icon.rc)
endif()
