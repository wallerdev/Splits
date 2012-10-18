//
//  CoreApplication.cpp
//  SplitsCore
//
//  Created by Edward Waller on 10/17/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#include "CoreApplication.h"
#include <sstream>

CoreApplication::CoreApplication(std::shared_ptr<WebBrowserInterface> browser, std::string settings_file) : _browser(browser), _settings_file(settings_file) {
    _browser->LoadHTML("<html>\
                        <body bgcolor=\"black\">\
                           <h1 id=\"timer\" style=\"color: lightgreen; font-family: Helvetica Neue; \"></h1>\
                        </body>\
                        </html>"
                       );
}

void CoreApplication::LoadSplits(std::string file) {
    
}

void CoreApplication::SaveSplits(std::string file) {
    
}

void CoreApplication::StartTimer() {
    _timer.Start();
}

void CoreApplication::StopTimer() {
    _timer.Stop();
}

void CoreApplication::ResetTimer() {
    
}

void CoreApplication::ChangeSetting(std::string key, std::string value) {
    
}

void CoreApplication::Update() {
    std::string elapsed_time = _timer.GetTimeElapsedDisplay();
    std::stringstream javascript_ss;
    javascript_ss << "document.getElementById('timer').innerText = \"" << elapsed_time << "\";";
    
    _browser->RunJavascript(javascript_ss.str());
}