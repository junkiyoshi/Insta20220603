#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(2);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int i = 0; i < 2; i++) {

		this->noise_seed_list.push_back(ofRandom(1000));
		this->noise_param_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int radius = 320;
	int span = 28;

	for (int deg_start = 1; deg_start < 360; deg_start += 90) {

		for (int deg = deg_start; deg < deg_start + 88; deg += 2) {

			for (int i = 0; i < this->noise_seed_list.size(); i++) {

				auto noise_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
				auto noise_param = ofMap(ofNoise(this->noise_seed_list[i], deg * 0.025 + this->noise_param_list[i]), 0, 1, 0.5, 1.0);

				this->mesh.addVertex(glm::vec3(radius * noise_param * cos(deg * DEG_TO_RAD), radius * noise_param * sin(deg * DEG_TO_RAD), 0));

				if (i > 0) {

					this->mesh.addIndex(this->mesh.getNumVertices() - 1);
					this->mesh.addIndex(this->mesh.getNumVertices() - 2);
				}

				if (deg > deg_start) {

					this->mesh.addIndex(this->mesh.getNumVertices() - 1);
					this->mesh.addIndex(this->mesh.getNumVertices() - this->noise_seed_list.size() - 1);
				}

				if (i % 2 == 0) {

					this->mesh.addColor(ofColor(0, 0, 255));
				}
				else {

					this->mesh.addColor(ofColor(255, 0, 0));
				}
			}
		}
	}

	for (int i = 0; i < this->noise_param_list.size(); i++) {

		this->noise_param_list[i] += 0.008;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->mesh.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}