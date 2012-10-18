//
//  Browser.mm
//  Splits
//
//  Created by Edward Waller on 10/17/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#include "Browser.h"

Browser::Browser(WebView *web_view) : _load_completed(false) {
    _web_view = web_view;
}

void Browser::LoadHTML(std::string html) {
    _load_completed = false;
    [[_web_view mainFrame] loadHTMLString:[[NSString alloc] initWithUTF8String:&html[0]] baseURL:nil];
}

void Browser::RunJavascript(std::string javascript) {
    [[_web_view windowScriptObject] evaluateWebScript:[[NSString alloc] initWithUTF8String:&javascript[0]]];
}

bool Browser::IsLoadCompleted() {
    return _load_completed;
}

void Browser::set_load_completed(bool value) {
    _load_completed = value;
}