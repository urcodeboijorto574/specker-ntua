#include "specker1n.hpp"
#include "specker2n.hpp"
#include "specker3n.hpp"
using namespace std;

#ifndef CONTEST
int main() {
	// Take this game as an example, and continue creating and playing on your own. Have fun! :D
	Game specker(3, 4);
	specker.addHeap(10);
	specker.addHeap(20);
	specker.addHeap(17);
	specker.addPlayer(new SneakyPlayer("Tom"));
	specker.addPlayer(new SpartanPlayer("Mary"));
	specker.addPlayer(new GreedyPlayer("Alan"));
	specker.addPlayer(new RighteousPlayer("Robin"));
	//specker.addPlayer(new pi20b072("John"));
	specker.play(cout);
	return 0;
}
#endif
