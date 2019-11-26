#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "window.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  bool isBlack = true;
  size_t size;

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
	  if (n % 2 != 0 || n < 4) continue;
	  isBlack = true;
	  size = n;
	  g.init(n);
	  // init central 2*2 cells
	  g.setPiece(n / 2, n / 2 - 1, Colour::White);
	  g.setPiece(n / 2 - 1, n / 2, Colour::White);
	  g.setPiece(n / 2, n / 2, Colour::Black);
	  g.setPiece(n / 2 - 1, n / 2 - 1, Colour::Black);
	  cout << g;
    }
	else if (cmd == "play") {
		int r = 0, c = 0;
		cin >> r >> c;
		if (r < 0 || c < 0 || r >= size || c >= size) continue;
		Colour colour;
		if (isBlack) colour = Colour::Black;
		else colour = Colour::White;
		try {
			g.setPiece(r, c, colour);
			cout << g;
			isBlack = !isBlack;
			if (!g.isFull()) continue;

			// now, we can get the result
			Colour winner = g.whoWon();
			if (winner == Colour::Black) {
				cout << "Black wins!" << endl;
			}
			else if (winner == Colour::NoColour) {
				cout << "Tie!" << endl;
			}
			else {
				cout << "White wins!" << endl;
			}
			break;
		} catch (int exception) {
			continue;
		}
	}
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}

