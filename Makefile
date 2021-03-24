CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -g
EXEC = cc3k 
MAINOBJ = main.o
FLOOROBJ = grid.o chamber.o
CHAROBJ = character.o thing.o
PLAYEROBJ = player.o human.o elf.o orc.o dwarf.o
ENEMYOBJ = enemy.o dragon.o merchant.o phoenix.o goblin.o werewolf.o vampire.o troll.o
ITEMOBJ = item.o potion.o treasure.o PH.o WA.o WD.o BD.o BA.o RH.o DH.o NH.o MH.o SH.o
OBJECTS = ${MAINOBJ} ${FLOOROBJ} ${CHAROBJ} ${PLAYEROBJ} ${ENEMYOBJ} ${ITEMOBJ}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
