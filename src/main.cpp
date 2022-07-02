#include "ofApp.h"

int main() {

	ofGLFWWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(640, 720);
	ofCreateWindow(settings);

	ofRunApp(new ofApp());

}
