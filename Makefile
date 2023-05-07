CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -g
EXEC=cc3k 
SRC=src
OBJ=obj

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRCS=$(call rwildcard,,*.cpp)
OBJECTS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

$(info $$var is [${SRCS}])
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

${OBJ}/%.o: ${SRC}/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -r ${OBJECTS} ${EXEC} ${DEPENDS}