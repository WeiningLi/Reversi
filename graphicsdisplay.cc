#include "graphicsdisplay.h"
#include "observer.h"
#include "subject.h"
#include "info.h"
#include "state.h"
#include "window.h"
using namespace std;

/*
class GraphicsDisplay : public Observer<Info, State> {
	const int gridSize;
	const int wSize = 500;
 */

GraphicsDisplay::GraphicsDisplay(int n) : gridSize{ n }, window { wSize, wSize } {
	window.fillRectangle(0, 0, wSize, wSize, Xwindow::Blue);
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
	Info cInfo = whoNotified.getInfo();
	int unit = wSize / gridSize;
	if (cInfo.colour == Colour::Black) window.fillRectangle(cInfo.col * unit, cInfo.row * unit, unit, unit, Xwindow::Black);
	if (cInfo.colour == Colour::White) window.fillRectangle(cInfo.col * unit, cInfo.row * unit, unit, unit, Xwindow::White);
	if (cInfo.colour == Colour::NoColour) window.fillRectangle(cInfo.col * unit, cInfo.row * unit, unit, unit, Xwindow::Blue);
}

