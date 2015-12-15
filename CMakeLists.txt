cmake_minimum_required(VERSION 3.3)
project(pa5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Advantage.cpp Advantage.h Agent.cpp Agent.h AggressiveAgentStrategy.cpp AggressiveAgentStrategy.h DefaultAgentStrategy.cpp DefaultAgentStrategy.h ErrorContext.cpp ErrorContext.h Exceptions.cpp Exceptions.h Food.cpp Food.h Game.cpp Game.h Gaming.cpp Gaming.h GamingTests.cpp GamingTests.h Piece.cpp Piece.h Resource.cpp Resource.h Simple.cpp Simple.h Strategic.cpp Strategic.h Strategy.cpp Strategy.h)
add_executable(pa5 ${SOURCE_FILES})