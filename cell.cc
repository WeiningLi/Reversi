#include <iostream>
#include "cell.h"
#include "subject.h"
#include "observer.h"
#include "state.h"
#include "info.h"
using namespace std;

/*
class Cell : public Subject<Info, State>, public Observer<Info, State> {
  const size_t r, c;
  Colour colour = Colour::NoColour;
*/

// set location
Cell::Cell(size_t r, size_t c) : r{ r }, c{ c } {}

// Place a piece of given colour here.
void Cell::setPiece(Colour colour) {
	this->colour = colour;
	// dont care direction of new piece
	State newS = State{ StateType::NewPiece, colour, Direction::NE };
	setState(newS);
}

// Toggles my colour.
void Cell::toggle() {
	if (colour == Colour::Black) colour = Colour::White;
	else if (colour == Colour::White) colour = Colour::Black;
	else return;
}

Info Cell::getInfo() const {
	Info cInfo = Info{ r, c, colour };
	return cInfo;
}

Direction getDirect(size_t row, size_t col, size_t crow, size_t ccol) {
	if (row < crow) {
		if (col < ccol) return Direction::SE;
		else if (col == ccol) return Direction::S;
		else return Direction::SW;
	}
	else if (row == crow) {
		if (col < ccol) return Direction::E;
		else return Direction::W;
	}
	else {
		if (col < ccol) return Direction::NE;
		else if (col == ccol) return Direction::N;
		else return Direction::NW;
	}
}

// My neighbours will call this when they've changed state
void Cell::notify(Subject<Info, State> &whoFrom) {
	if (colour != Colour::NoColour) {
		State stateF = whoFrom.getState();
		Direction direction = getDirect(r, c, whoFrom.getInfo().row, whoFrom.getInfo().col);
		Direction reverseD = getDirect(whoFrom.getInfo().row, whoFrom.getInfo().col, r, c);
		State newS;
		// notified by a new piece
		// no reaction when neighbour has same colour
		if (stateF.type == StateType::NewPiece && colour != whoFrom.getInfo().colour) newS = State{ StateType::Relay, colour, direction };
		// notified by a relay of same colour on a line fron new piece
		else if (stateF.type == StateType::Relay && direction == stateF.direction && colour == stateF.colour) newS = State{ StateType::Relay, colour, direction };
		// notified by a relay of diff colour on a line from new piece
		else if (stateF.type == StateType::Relay && direction == stateF.direction && colour != stateF.colour) newS = State{ StateType::Reply, colour, direction };
		// notified by a reply, trace back to new piece
		else if (stateF.type == StateType::Reply && stateF.direction == reverseD && getState().type == StateType::Relay) {
			toggle();
			newS = State{ StateType::Reply, colour, reverseD };
		}
		else return;
		setState(newS);
		notifyObservers();
	}
}


