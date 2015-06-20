CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x
OBJECTS = Command.o Card.o Table.o Deck.o main.o Hand.o Player.o Game.o Strategy.o HumanStrategy.o ComputerStrategy.o View.o TextView.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
