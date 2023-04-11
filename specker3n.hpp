#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Game {
public:
	Game(int heaps, int players) {
		currentheaps = currentplayers = 0;
		totalheaps = heaps, totalplayers = players;
		nowplaying=0;
		heap = new int[totalheaps];
		allplayers = new Player*[totalplayers];
		heapsOK = playersOK = false;
		state = nullptr;
	}
	~Game() {
		delete state;
		for (int i=0; i<currentplayers; i++)
			delete allplayers[i];
		delete allplayers;
	}

	void addHeap(int coins) {
			if (heapsOK)
				throw logic_error("not enough heaps.. maybe poker would be a better game for ya, eh?");
			heap[currentheaps++] = coins;
			if (currentheaps==totalheaps)
				heapsOK=true;
	}
	void addPlayer(Player *player) {
		if (playersOK)
			throw logic_error("not enough seats, and don't invite people without asking...>:(");

		allplayers[currentplayers++] = player;
		if (currentplayers==totalplayers)
			playersOK = true;
	}
	void play(ostream &out) {
		if (heapsOK && playersOK) {
			state = new State(totalheaps, heap, totalplayers);
			do {
				if (nowplaying==totalplayers) nowplaying=0;
				out << "State: " << *state << endl;
				out << *allplayers[nowplaying] << " " << allplayers[nowplaying]->play(*state) << endl;
				state->next(allplayers[nowplaying++]->play(*state));
			} while (!state->winning());

			out << "State: " << *state << endl;
			out << *allplayers[nowplaying++-1] << " wins" << endl;
		}
		else throw logic_error("give more info, and I won't beat your ass :)");
	}
	int getPlayers() const { return currentplayers; }
	const Player *getPlayer(int p) const {
		if (p<0) throw logic_error("negative position. Give 0 or positive... or go home.. there's always a choice");
		else if (p>=currentplayers) throw logic_error("too big of a number.. tell a friend to join!");
		return allplayers[p];
	}

private:
	int currentheaps, currentplayers, totalheaps, totalplayers;
	int * heap;
	bool heapsOK, playersOK;
	State * state;
	int nowplaying;
	Player ** allplayers;
};
