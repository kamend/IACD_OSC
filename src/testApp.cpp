#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	
	
	lines.setMode(OF_PRIMITIVE_LINES);
	linesMovement=0;
	linesMovementSpeed =2;
	linesOffset = 20;
	intermediatePoints = 200;
	mouthHeight = 1.0;
	eyeLeft = 1.0;
	eyeRight = 1.0;
	eyebrowLeft =10.0;
	eyebrowRight = 10.0;
	
	osc.setup(8338);
}

//--------------------------------------------------------------
void testApp::update(){
	
	// OSC
	
	while(osc.hasWaitingMessages()) {
		ofxOscMessage m;
		osc.getNextMessage(&m);
		
				
		string address = m.getAddress();
		
		
		if(address == "/gesture/mouth/height") {
			float v = m.getArgAsFloat(0);
			v = ofClamp(v, 1.0, 4.5);
			
			if(abs(mouthHeight - v) > 0.1) {
				mouthHeight = v;
			}
			
		} else if(address == "/gesture/eye/left") {
			float v = m.getArgAsFloat(0);

			v = ofClamp(v, 2.0, 3.0);
			eyeLeft = ofMap(v, 2.0,3.0,0.0,5.0);

		} else if(address == "/gesture/eye/right") {
			float v = m.getArgAsFloat(0);
			
			v = ofClamp(v, 2.0, 3.0);
			eyeRight = ofMap(v, 2.0,3.0,0.0,5.0);
			
		} else if(address == "/gesture/eyebrow/left") {
			float v = m.getArgAsFloat(0);
			v = ofClamp(v, 6.0, 8.0);
			eyebrowLeft =ofMap(v, 6.0,8.0, 10.0,40.0);
	
			
		} else if(address == "/gesture/eyebrow/right") {
			float v = m.getArgAsFloat(0);
			v = ofClamp(v, 6.0, 8.0);
			eyebrowRight = ofMap(v, 6.0,8.0, 10.0,40.0);
		}
		
	}
	
	linesMovementSpeed = (eyeRight + eyeLeft) / 2.0;
	linesOffset = (eyebrowRight + eyebrowLeft) / 2.0;

	lines.clear();

	float gridSizeWidth = 1280;
	float gridSizeHeight = 1280;

	
	for(float y=-gridSizeHeight/2+linesMovement;y <gridSizeHeight/2+linesMovement; y+= linesOffset) {
		ofVec2f startPoint = ofVec2f(-gridSizeWidth/2, y);
		ofVec2f endPoint = ofVec2f(gridSizeWidth/2, y);
		
		float distanceBetweenIntermediatePoints = (endPoint.x - startPoint.x) / intermediatePoints;
		
		
		ofVec2f prevVertex = startPoint;
	
		
		for(int pointNum=1;pointNum <= intermediatePoints; pointNum++) {
			
			ofVec2f currentVertex = ofVec2f(startPoint.x+distanceBetweenIntermediatePoints*pointNum, startPoint.y);
			

			
			float angle = ofMap(pointNum, 0, intermediatePoints, -3600*mouthHeight,3600*mouthHeight);
			
			currentVertex += sin(ofDegToRad(angle))*mouthHeight*2.0;
			
			//currentVertex += ofSignedNoise(prevVertex.x, prevVertex.y)*10.0;
			
			lines.addVertex(prevVertex);
			lines.addVertex(currentVertex);
			
			ofColor c;
			c.set(255,255,255,ofMap(prevVertex.y, -gridSizeHeight/2, gridSizeHeight/2, 50,255));
			
			lines.addColor(c);
			lines.addColor(c);
			
			prevVertex = currentVertex;
		}
		
	}
	
	linesMovement += linesMovementSpeed;
	
	if(linesMovement >= linesOffset) {
		linesMovement-= linesOffset;
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0, 0, 0);

	
	ofPushMatrix();
	
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofRotateZ(45);
	lines.drawFaces();
	ofPopMatrix();
	
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}