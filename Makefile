CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x
OBJECTS = Command.o Card.o Table.o Deck.o main.o Hand.o __tests__.o Game.o Player.o HumanPlayer.o ComputerPlayer.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
