#include <iostream>
#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "info.h"
#include "state.h"
#include "window.h"
#include <vector>
using namespace std;

/*
class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  TextDisplay *td = nullptr; // The text display.
  Observer<Info, State> *ob = nullptr;  // Another observer (intent:  graphics)
*/
Grid::~Grid() {
	delete td;
	delete ob;
}
 
void Grid::setObserver(Observer<Info, State> *ob) {
	delete (this->ob);
	this->ob = ob;
}

// Is the game over, i.e., is the grid full?
bool Grid::isFull() const {
	bool full = true;
	for (auto row: theGrid) {
		for (auto c : row) {
			if (c.getInfo().colour == Colour::NoColour) {
				full = false;
				break;
			}
		}
		if (full == false) break;
	}
	return full;
}

// Who has more pieces when the board is full?
Colour Grid::whoWon() const {
	int diff = 0;
	for (auto row : theGrid) {
		for (auto c : row) {
			if (c.getInfo().colour == Colour::Black) ++diff;
			if (c.getInfo().colour == Colour::White) --diff;
		}
	}
	if (diff == 0) return Colour::NoColour;
	else if (diff > 0) return Colour::Black;
	else return Colour::White;
}

// Sets up an n x n grid.  Clears old grid, if necessary.
void Grid::init(size_t n) {
	// clear old grid
	theGrid.erase(theGrid.begin(), theGrid.end());
	delete td;

	// init new fields
	for (size_t row = 0; row < n; ++row) {
		vector<Cell> nRow;
		for (size_t col = 0; col < n; ++col) {
			Cell nc{ row, col };
			nRow.emplace_back(nc);
		}
		theGrid.emplace_back(nRow);
	}
	td = new TextDisplay{ n };
	setObserver(new GraphicsDisplay{ n });

	// attach observers
	for (auto &row : theGrid) {
		for (auto &c : row) {
			const Info cInfo = c.getInfo();
			// attach text/graphics display observer
			c.attach(td);
			c.attach(ob);
			// change size_t to int for negative
			int tempR = cInfo.row;
			int tempC = cInfo.col;
			for (int i = tempR - 1; i <= tempR + 1; ++i) {
				for (int j = tempC - 1; j <= tempC + 1; ++j) {
					if ((i >= 0) && (j >= 0) && (i < theGrid.size()) && (j < theGrid.size()) && !(i == tempR && j == tempC)) c.attach(&(theGrid[i][j]));
				}
			}
		}
	}
}

// Plays piece at row r, col c.
void Grid::setPiece(size_t r, size_t c, Colour colour) {
	if (theGrid[r][c].getInfo().colour != Colour::NoColour) throw 1337;
	theGrid[r][c].Cell::setPiece(colour);
	theGrid[r][c].notifyObservers();
}

// Flips piece at row r, col c.
void Grid::toggle(size_t r, size_t c) {}

ostream &operator<<(ostream &out, const Grid &g) {
	out << *(g.td);
	return out;
}

