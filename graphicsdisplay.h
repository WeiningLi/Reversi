#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"
class Cell;

class GraphicsDisplay : public Observer<Info, State> {
	const int gridSize;
	const int wSize = 500;
	Xwindow window;

public:
	GraphicsDisplay(int n);
	void notify(Subject<Info, State> &whoNotified) override;
};
#endif

