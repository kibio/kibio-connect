// =============================================================================
//
// Copyright (c) 2009-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "KibioConnectApp.h"



void KibioConnectApp::exit()
{
    server->unregisterWebSocketEvents(this); // not needed
}


void KibioConnectApp::setup()
{
    ofxZeroconf::RegisterBrowseServiceEvents(this);

    browseRef = ofxZeroconf::browse("_kibio_player._tcp","local.");

    ofSetFrameRate(30);
    ofEnableAlphaBlending();

    ofSetLogLevel(OF_LOG_NOTICE);

    ofxWebSocketServerBasic::Settings settings;
    settings.port = 8081;   
//    settings.documentRoot = "kibio.github.com";

    server = ofxWebSocketServerBasic::instance(settings);
    server->registerWebSocketEvents(this);
    server->start();

}


void KibioConnectApp::update()
{
}


void KibioConnectApp::draw() {
    ofBackground(255);
    ofSetColor(255);
    
    size_t numConnected = server->getNumClientsConnected();
    
    ofSetColor(255,255,0);
    ofFill();
    
    int pad = 5;
    string txt = "Num Connected: " + ofToString(numConnected);
    ofPoint posTop(pad,10+pad);
    ofDrawBitmapStringHighlight(txt,posTop,ofColor(0),ofColor(255));
    
}


void KibioConnectApp::gotMessage(ofMessage msg)
{
}


void KibioConnectApp::onOpenEvent(ofxWebSocketEventArgs& _evtArgs)
{
    ofSendMessage("Got open event.");
}


void KibioConnectApp::onCloseEvent(ofxWebSocketEventArgs& _evtArgs)
{
    ofSendMessage("Got close event.");
}


void KibioConnectApp::onFrameReceivedEvent(ofxWebSocketFrameEventArgs& _evtArgs)
{
    ofSendMessage("Got frame received event.");
    cout << "aaaaa---> " << _evtArgs.hasError() << endl;
    if(_evtArgs.frame.isBinary()) {
        cout << "binary frame=" << endl;
    } else {
        commandInterpreter(_evtArgs.frame.getText());
    }    
}


void KibioConnectApp::onFrameSentEvent(ofxWebSocketFrameEventArgs& _evtArgs)
{
    ofSendMessage("Got frame sent event.");
}


void KibioConnectApp::onErrorEvent(ofxWebSocketEventArgs& _evtArgs)
{
    ofSendMessage("Got error event.");
}


void KibioConnectApp::commandInterpreter(const string& data) {
    ofxJSONElement json;
    if(json.parse(data)) {
        if(json.isMember("command") && json["command"].isString()) {
            
            string command = json["command"].asString();
            
            cout << "command = " << command << endl;
            
            if(startsWith(command,"video-control")) {
                
            } else if(startsWith(command,"video-info")) {
                
            } else {
                
            }
            
            
            
            /*
             VIDEO_CONTROL_BACKWARD = "video-control-backward";
             VIDEO_CONTROL_PLAY     = "video-control-play";
             VIDEO_CONTROL_PAUSE    = "video-control-pause";
             VIDEO_CONTROL_STOP     = "video-control-stop";
             VIDEO_CONTROL_FORWARD  = "video-control-forward";
             VIDEO_CONTROL_POSITION = "video-control-position";
             */
            
        } else {
            cout << "no command " << endl;
        }
        
    } else {
        cout << "invalid packet json: " << data << endl;
    }
    
    cout << "frame=" << data << endl;
}


bool KibioConnectApp::startsWith(const string& target, const string& prefix)
{
    return !target.compare(0, prefix.size(), prefix);
}
