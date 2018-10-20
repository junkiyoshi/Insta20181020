#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	int font_size = 350;
	font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	string word = "B";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);

	this->fbo.end();

	ofPixels pixels;
	this->fbo.readToPixels(pixels);

	int span = 10;

	ofColor pix_color;
	for (int x = 0; x < this->fbo.getWidth(); x += span) {

		for (int y = 0; y < this->fbo.getHeight(); y += span) {

			pix_color = pixels.getColor(x, y);
			if (pix_color != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5));
			}
		}
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	ofColor color;
	for (ofPoint& point : this->locations) {
		
		color.setHsb(ofRandom(255), 239, 239);
		float depth = 100 * ofNoise(point.x * 0.02, point.y * 0.02, ofGetFrameNum() * 0.03);
		
		ofSetColor(color);
		ofDrawBox(point - ofPoint(0, 0, depth * 0.5), 10, 10, depth);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}