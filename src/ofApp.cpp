#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetLogLevel(OF_LOG_VERBOSE);

	ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinect::Device::getInstalledCount() << " installed devices.";

	// Open Kinect.
	kinectSetup(720);

	// Load shader.
	auto shaderSettings = ofShaderSettings();
	shaderSettings.shaderFiles[GL_VERTEX_SHADER] = "shaders/perpixel.vert";
	shaderSettings.shaderFiles[GL_FRAGMENT_SHADER] = "shaders/perpixel.frag";
	shaderSettings.bindDefaults = true;
	if (shader.setup(shaderSettings)) {
		ofLogNotice(__FUNCTION__) << "Success loading shader!";
	}

	plane.set(kColorWidth, kColorHeight, 10, 10);
	plane.mapTexCoords(0, 0, kColorWidth, kColorHeight);
}

//--------------------------------------------------------------
void ofApp::exit() {
	kinectDevice.close();
}

//--------------------------------------------------------------
void ofApp::update() {
	//
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	if (kinectDevice.isStreaming()) {
		shader.begin();

		/*
		shader.setUniform1f("uSpriteSize", pointSize);				
		shader.setUniformTexture("uDepthTex", kinectDevice.getDepthTex(), 1);
		shader.setUniformTexture("uDepthTex", kinectDevice.getDepthInColorTex(), 1);
		shader.setUniformTexture("uColorTex", kinectDevice.getColorTex(), 3);
		shader.setUniformTexture("uColorTex", kinectDevice.getColorInDepthTex(), 3);
		shader.setUniformTexture("uWorldTex", kinectDevice.getColorToWorldTex(), 2);
		shader.setUniformTexture("uWorldTex", kinectDevice.getDepthToWorldTex(), 2);
		shader.setUniform2i("uFrameSize", kinectDevice.getColorTex().getWidth(), kinectDevice.getColorTex().getHeight());
		shader.setUniform2i("uFrameSize", kinectDevice.getDepthTex().getWidth(), kinectDevice.getDepthTex().getHeight());
		}
		*/

		shader.setUniformTexture("uColorTex", kinectDevice.getColorTex(), 0);
		shader.setUniformTexture("uDepthTex", kinectDevice.getDepthInColorTex(), 1);
		shader.setUniform2i("uFrameSize", kinectDevice.getColorTex().getWidth(), kinectDevice.getColorTex().getHeight());

		ofPushMatrix();
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
		plane.draw();
		ofPopMatrix();

		shader.end();
	}

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 2) + " FPS", 10, 20);
}

void ofApp::kinectGetAllDims() {
	cout << "colorTex: " << ofToString(kinectDevice.getColorTex().getWidth()) << " x " << ofToString(kinectDevice.getColorTex().getHeight()) << endl;
	cout << "depthTex: " << ofToString(kinectDevice.getDepthTex().getWidth()) << " x " << ofToString(kinectDevice.getDepthTex().getHeight()) << endl;
	cout << "colorInDepthTex: " << ofToString(kinectDevice.getColorInDepthTex().getWidth()) << " x " << ofToString(kinectDevice.getColorInDepthTex().getHeight()) << endl;
	cout << "depthInColorTex: " << ofToString(kinectDevice.getDepthInColorTex().getWidth()) << " x " << ofToString(kinectDevice.getDepthInColorTex().getHeight()) << endl;
	cout << "colorToWorldTex: " << ofToString(kinectDevice.getColorToWorldTex().getWidth()) << " x " << ofToString(kinectDevice.getColorToWorldTex().getHeight()) << endl;
	cout << "depthToWorldTex: " << ofToString(kinectDevice.getDepthToWorldTex().getWidth()) << " x " << ofToString(kinectDevice.getDepthToWorldTex().getHeight()) << endl;
}


void ofApp::kinectSetup(int res) {
	ofLogNotice(__FUNCTION__) << "Found " << ofxAzureKinect::Device::getInstalledCount() << " installed devices.";

	// Open Kinect.
	if (kinectDevice.open()) {
		auto kinectSettings = ofxAzureKinect::DeviceSettings();

		kinectSettings.updateIr = false;
		kinectSettings.updateColor = true;
		kinectSettings.updateVbo = false;

		if (res == 720) {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_720P; // 1280 * 720 16:9
			kColorWidth = 1280;
			kColorHeight = 720;
		}
		else if (res == 1440) {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_1440P; // 2560 * 1440 16:9
			kColorWidth = 2560;
			kColorHeight = 1440;
		}
		else if (res == 1536) {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_1536P; // 2048 * 1536 4:3
			kColorWidth = 2048;
			kColorHeight = 1536;
		}
		else if (res == 2160) {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_2160P; // 3840 * 2160 16:9
			kColorWidth = 3840;
			kColorHeight = 2160;
		}
		else if (res == 3072) {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_3072P; // 4096 * 3072 4:3
			kColorWidth = 4096;
			kColorHeight = 3072;
		}
		else {
			kinectSettings.colorResolution = K4A_COLOR_RESOLUTION_1080P; // 1920 * 1080 16:9
			kColorWidth = 1920;
			kColorHeight = 1080;
		}

		kinectDevice.startCameras(kinectSettings);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
	
}
