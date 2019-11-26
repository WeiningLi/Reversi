#include "textdisplay.h"
#include "observer.h"
#include "subject.h"
#include "info.h"
#include "state.h"
using namespace std;

/*
class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
  */

TextDisplay::TextDisplay(int n) : gridSize{ n } {
	for (size_t row = 0; row < n; ++row) {
		vector<char> nRow;
		for (size_t col = 0; col < n; ++col) {
			char c = '-';
			nRow.emplace_back(c);
		}
		nRow.emplace_back('\n');
		theDisplay.emplace_back(nRow);
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (auto row : td.theDisplay) {
		for (auto c : row) out << c;
	}
	return out;
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	Info cInfo = whoNotified.getInfo();
	char nc;
	if (cInfo.colour == Colour::Black) nc = 'B';
	else if (cInfo.colour == Colour::NoColour) nc = '-';
	else nc = 'W';
	theDisplay[cInfo.row][cInfo.col] = nc;
}

