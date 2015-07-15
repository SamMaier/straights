CXX = g++
CXXFLAGS = -g -Wall -MMD -std=c++0x `pkg-config gtkmm-2.4 --cflags --libs`
OBJECTS = src/Command.o src/Card.o src/Table.o src/Deck.o src/main.o src/Hand.o src/Player.o src/Game.o src/Strategy.o src/HumanStrategy.o src/ComputerStrategy.o src/View.o src/TextView.o src/Subject.o src/Observer.o src/GameController.o src/GtkView.o src/ImageFactory.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
