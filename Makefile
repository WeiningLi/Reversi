CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = Reversi
OBJECTS = main.o cell.o grid.o textdisplay.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

