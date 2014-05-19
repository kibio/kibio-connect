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


#pragma once


#include "ofMain.h"
#include "ofBaseApp.h"
#include "ofxJSONElement.h"
#include "ofxWebSocketServerBasic.h"
#include "ofxZeroconf.h"


class KibioConnectApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void gotMessage(ofMessage msg);
    
    void onOpenEvent(ofxWebSocketEventArgs& _evtArgs);
    void onCloseEvent(ofxWebSocketEventArgs& _evtArgs);
    void onFrameReceivedEvent(ofxWebSocketFrameEventArgs& _evtArgs);
    void onFrameSentEvent(ofxWebSocketFrameEventArgs& _evtArgs);
    void onErrorEvent(ofxWebSocketEventArgs& _evtArgs);
    
    void commandInterpreter(const string& data);
    bool startsWith(const string& target, const string& prefix);

    ofxWebSocketServerBasic::Ptr server;
    
    Zeroconf::BrowseRef  browseRef;

    void onBrowseError(const Zeroconf::BrowseErrorEventArgs& args) {
        cout << "BROWSER ERROR: " << args.error.getMessage() << endl;
    }

    void onBrowseServiceFound(const Zeroconf::BrowseServiceEventArgs& args) {
        cout << "SERVICE FOUND" << endl;
        cout <<  ofToString(args.service) << endl;
        //        ofxZeroconf::resolve(args.service);
    }

    void onBrowseServiceRemoved(const Zeroconf::BrowseServiceEventArgs& args) {
        cout << "SERVICE REMOVED" << endl;
        cout <<  ofToString(args.service) << endl;

    }

    void onResolveError(const Zeroconf::BrowseErrorEventArgs& args) {
        cout << "RESOLVE ERROR" << endl;
        cout <<  ofToString(args.error.getMessage()) << endl;
    }

    void onServiceResolved(const Zeroconf::BrowseServiceEventArgs& args) {
        cout << "SERVICE RESOLVED" << endl;
        cout <<  ofToString(args.service) << endl;
        //        ofxZeroconf::resolveHost(args.service.getHost());
    }

    void onHostResolveError(const Zeroconf::BrowseErrorEventArgs& args) {
        cout << "HOST RESOLVE ERROR" << endl;
        cout <<  ofToString(args.error.getMessage()) << endl;
    }

    void onHostResolved(const Zeroconf::ResolveHostEventArgs& args) {
        cout << "HOST RESOLVED" << endl;
        cout <<  ofToString(args.ipAddress.toString()) << endl;
        cout <<  ofToString(args.ttl) << endl;
        cout <<  ofToString(args.options) << endl;
    }
};
