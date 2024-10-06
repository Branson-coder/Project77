# c++ compiler is g++ or clang
CXX = g++

# flags for the compiler
CXXFLAGS = -std=c++17 -Wall -Wextra
# flags required for sfml library compilation
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# all cpp files here
SOURCES = main.cpp Animation.cpp Wall.cpp Collider.cpp Player.cpp Room.cpp Projectile.cpp Weapon.cpp AK47.cpp AssaultRifle.cpp Enemy.cpp FastEnemy.cpp Item.cpp Heals.cpp

# .o files from the specific .cpp files
OBJECTS = $(SOURCES:.cpp=.o)

# ./game  (command in terminal to run game)
EXECUTABLE = games

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# this cleans up build files
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
