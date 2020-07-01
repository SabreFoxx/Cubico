cmake_minimum_required(VERSION 3.0)

project(cubico)

include_directories(thirdparty/)
include_directories(include/polyvox/)

# find_package(OpenGL REQUIRED) # Legacy OPENGL_gl_LIBRARY
find_package(OpenGL REQUIRED COMPONENTS OpenGL) # To use new GLVND OPENGL_opengl_LIBRARY instead of lagacy one
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
if (OpenGL_FOUND)
	include_directories(${OpenGL_INCLUDE_DIRS})
	link_libraries(OpenGL::OpenGL ${OpenGL_LIBRARIES}) # OpenGL::OpenGL helps us use new OPENGL_opengl_LIBRARY
endif()
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	link_libraries(${GLEW_LIBRARIES})
endif()
if (GLUT_FOUND)
	include_directories(${GLUT_INCLUDE_DIRS})
	link_libraries(${GLUT_LIBRARIES})
endif()

add_executable(cubico src/main.cpp)
add_executable(test_camera src/test_camera.cpp)
add_executable(test_vertex_array src/test_vertex_array.cpp)

add_library(glut_camera thirdparty/camera/Camera.cpp)
add_library(polyvox
	thirdparty/polyvox/AmbientOcclusionCalculator.cpp
	thirdparty/polyvox/AStarPathfinder.cpp
	thirdparty/polyvox/BaseVolume.cpp
	thirdparty/polyvox/CubicSurfaceExtractor.cpp
	thirdparty/polyvox/LowPassFilter.cpp
	thirdparty/polyvox/MarchingCubesSurfaceExtractor.cpp
	thirdparty/polyvox/Mesh.cpp
	thirdparty/polyvox/Picking.cpp
	thirdparty/polyvox/RawVolume.cpp
	thirdparty/polyvox/Raycast.cpp
	thirdparty/polyvox/Region.cpp
	thirdparty/polyvox/Vector.cpp
	thirdparty/polyvox/VolumeResampler.cpp
)
target_include_directories(polyvox PRIVATE thirdparty/polyvox/Impl)

target_link_libraries(cubico glut_camera GLU)
target_link_libraries(test_camera glut_camera GLU)
target_link_libraries(test_vertex_array glut_camera GLU)

install(TARGETS cubico RUNTIME DESTINATION bin)
