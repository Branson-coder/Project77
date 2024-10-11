# c++ compiler is g++ or clang
CXX = g++

# flags for the compiler
CXXFLAGS = -std=c++17 -Wall -Wextra
# flags required for sfml library compilation
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# all cpp files here
SOURCES = main.cpp Menu.cpp Animation.cpp Wall.cpp Collider.cpp Player.cpp Room.cpp Projectile.cpp Weapon.cpp AssaultRifle.cpp AK47.cpp M16.cpp Shotgun.cpp SawedOff.cpp Enemy.cpp FastEnemy.cpp Item.cpp Heals.cpp TankyEnemy.cpp NormalEnemy.cpp HUD.cpp

# .o files from the specific .cpp files
OBJECTS = $(SOURCES:.cpp=.o)

# ./game  (command in terminal to run game)
EXECUTABLE = game

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# this cleans up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# for debugging, copy paste this code:
# g++ -g main.cpp Menu.cpp Animation.cpp Wall.cpp Collider.cpp Player.cpp Room.cpp Projectile.cpp Weapon.cpp AssaultRifle.cpp AK47.cpp M16.cpp Shotgun.cpp SawedOff.cpp Enemy.cpp FastEnemy.cpp Item.cpp Heals.cpp TankyEnemy.cpp NormalEnemy.cpp HUD.cpp -lsfml-graphics -lsfml-window -lsfml-system -o debug