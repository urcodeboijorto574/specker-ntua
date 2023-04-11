#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Move {
public:
	//Take sc coins from heap sh and put tc coins to heap th.
	Move(int sh, int sc, int th, int tc)
		: sheap(sh), scoins(sc), theap(th), tcoins(tc) {};

	int getSource() const {return sheap;}
	int getSourceCoins() const {return scoins;}
	int getTarget() const {return theap;}
	int getTargetCoins() const {return tcoins;}

	friend ostream & operator << (ostream &out, const Move &move) {
		out << "takes " << move.getSourceCoins() << " coins from heap "
				<< move.getSource() << " and puts ";
		if (move.getTargetCoins()==0) out << "nothing";
		else out << move.getTargetCoins() << " coins to heap " << move.getTarget();
		return out;
	}

private:
	int sheap, scoins, theap, tcoins;
};

class State {
public:
	// State with h heaps, where the i-th heap starts with c[i] coins.
	//A total of n players are in the game, numbered from 0 to n-1,
	//and player 0 is the first to play.
	State(int h, const int c[], int n) {
		if (h<0) throw logic_error("give valid number of heaps you lunatic");
		heap = new int[h];
		player = new int[n];
		nheaps = h, nplayers = n;
		playing=0;
		for (int i=0; i<h; i++) heap[i]=c[i];
		for (int i=0; i<n; i++) player[i]=i;
	}
	~State() {delete[] heap; delete[] player;}

	void next(const Move &move) {
		int a = move.getSourceCoins();
		int b = move.getTargetCoins();
		// if (a==0) throw logic_error("invalid source coins, you smartass piece of shit");
		if (a<=b) throw logic_error("invalid target coins, you can't outspecker me boi");
		if (getCoins(move.getSource()) < a) throw logic_error("take less or go play frisbee");
		heap[move.getSource()]-=a;
		heap[move.getTarget()]+=b;
		if (nplayers==1) throw logic_error("give that dude a friend, he needs him more than this game ;)");
		if (playing < nplayers-1) playing++;
		else playing=0;
	}
	bool winning() const {
		for (int i=0; i<nheaps; i++)
			if (heap[i]!=0) return false;
		return true;
	}

	int getHeaps() const {return nheaps;}
	int getCoins(int h) const {
		if (h<0 || h>=nheaps)
			throw logic_error("invalid heap, c'mon it's not that hard");
		return heap[h];
	}
	int getPlayers() const {return nplayers;}
	int getPlaying() const {return playing;}

	friend ostream & operator << (ostream &out, const State &state) {
		for (int i=0; i< state.nheaps-1; i++)
			out << state.heap[i] << ", ";

		out << state.heap[state.nheaps-1] << " with " << state.getPlaying() << "/" <<
				state.getPlayers() << " playing next";
		return out;

	}
private:
	int *heap; int nheaps, nplayers;
	int *player;
	int playing;
};
