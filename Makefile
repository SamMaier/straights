CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = src/Command.o src/Card.o src/Table.o src/Deck.o src/main.o src/Hand.o src/Player.o src/Game.o src/Strategy.o src/HumanStrategy.o src/ComputerStrategy.o src/View.o src/TextView.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
