cmake_minimum_required(VERSION 3.9.1)
list(APPEND VerletSim_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/Simulation.cpp
	${CMAKE_CURRENT_LIST_DIR}/Particle.cpp
	${CMAKE_CURRENT_LIST_DIR}/Physics.cpp
)
