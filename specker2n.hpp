#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Player {
public:
	Player (const string &n): name(n) {}
	virtual ~Player() {}
	virtual const string & getType() const = 0;
	virtual Move play(const State &s) = 0;
	friend ostream &operator << (ostream &out, const Player &player) {
		return out << player.getType() << " player " << player.name;
	}
protected:
	string name;
};

class GreedyPlayer : public Player {
public:
	GreedyPlayer(const string &name): Player(name), type("Greedy") {}
	~GreedyPlayer() override {}

	const string &getType() const override {return type;}
	Move play(const State &s) override {
		int a = s.getHeaps();
		int b=0, d;
		int morecoins=s.getCoins(0);
		for (int i=1; i<a; i++) {
			if (morecoins < (d=s.getCoins(i)))
				morecoins = d, b=i;
		}
		return Move(b, morecoins, 0, 0);
	}

private:
	string type;
};
class SpartanPlayer: public Player {
public:
	SpartanPlayer(const string &name): Player(name), type("Spartan") {}
	~SpartanPlayer() override {}

	const string &getType() const override {return type;}
	Move play(const State &s) override {
		int a = s.getHeaps();
		int b, d;
		int morecoins=0;
		for (int i=0; i<a; i++)
			if (morecoins < (d=s.getCoins(i))) b = i, morecoins = d;
		return Move(b, 1, 0, 0);
	}

private:
	string type;
};
class SneakyPlayer: public Player {
public:
	SneakyPlayer(const string &name): Player(name), type("Sneaky") {}
	~SneakyPlayer() override {}

	const string &getType() const override { return type; }
	Move play(const State &s) override {
		int a = s.getHeaps();
		int b, d;
		int lesscoins;
		bool initiallesscoinsfound=false;
		for (int i=0; i<a; i++) {
			d = s.getCoins(i);
			if (d==0) continue;
			else if (!initiallesscoinsfound)
				b=i, lesscoins=d, initiallesscoinsfound=true;
			else if (lesscoins > d)
				b=i, lesscoins=d;
		}
		return Move(b, lesscoins, 0, 0);
	}

private:
	string type;
};
class RighteousPlayer: public Player {
public:
	RighteousPlayer(const string &name): Player(name), type("Righteous") {}
	~RighteousPlayer() override {}

	const string &getType() const override {return type;}
	Move play(const State &s) override {
		int a = s.getHeaps();
		int lessheap=0, moreheap=0;
		int morecoins=0, lesscoins=s.getCoins(0);
		int d;
		for (int i=0; i<a; i++) {
			d=s.getCoins(i);
			if (morecoins < d)
				moreheap=i, morecoins = d;
			if (lesscoins > d)
				lessheap=i, lesscoins = d;
		}
		if (morecoins%2==1) morecoins+=2;
		if (lesscoins%2==1) lesscoins+=2;
		return Move (moreheap, morecoins/2, lessheap, morecoins/2-1);
	}

private:
	string type;
};

class pi20b072 : public Player {
	string type;
public:
	pi20b072(const string &name) : Player(name), type("Humble") {}
	~pi20b072() override {}

	const string &getType() const override { return type; }
	Move play(const State &s) override {
		if (s.getPlayers() == 2) {

			if (s.getHeaps() == 2) {
				if (s.getCoins(0) == s.getCoins(1))
					return Move(1, 0, 0, 0);
				else if (s.getCoins(0) > s.getCoins(1))
					return Move(s.getCoins(0)-s.getCoins(1), 0, 0, 0);
				else
					return Move(s.getCoins(1)-s.getCoins(0), 1, 0, 0);
			}
			else if (s.getHeaps() == 3) {
				int a = s.getCoins(0); bool samevals = true;
				for (int i=1; i<3; ++i)
					if (s.getCoins(i) != a) { samevals = false; break; }
				if (samevals) return Move(0, s.getCoins(2), 0, 0);
				else if (s.getCoins(0) == s.getCoins(1)) return Move(2, s.getCoins(2), 0, 0);
				else if (s.getCoins(0) == s.getCoins(2)) return Move(1, s.getCoins(1), 0, 0);
				else if (s.getCoins(1) == s.getCoins(2)) return Move(0, s.getCoins(0), 0, 0);
				else {
					int b;
					int morecoins=0;
					for (int i=0; i<s.getHeaps(); i++)
						if (morecoins < s.getCoins(i)) b = i, morecoins = s.getCoins(i);
					return Move(b, 1, 0, 0);

				}
			}

		}
		else if (s.getPlayers() == 3) {
			if (s.getHeaps() == 2) ;
		}

		int okheap;
		for (int i=0; i<s.getHeaps(); ++i)
			if (s.getCoins(i) != 0) { okheap = i; break; }
		Move(1, okheap, 0, 0);
	}
};
