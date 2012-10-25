//
//  CoreApplication.cpp
//  SplitsCore
//
//  Created by Edward Waller on 10/17/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#include "CoreApplication.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <SplitsCore/Split.h>

bool StartsWith(std::string input, std::string prefix) {
    return !input.compare(0, prefix.size(), prefix);
}

std::vector<std::string> SplitString(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

CoreApplication::CoreApplication(std::shared_ptr<WebBrowserInterface> browser, std::string settings_file) : _browser(browser), _settings_file(settings_file), _currentSplitIndex(0), _timer(new Timer) {
    _browser->LoadHTML("<html>\
                       <head>\
                       <script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js\"></script>\
                       <style type=\"text/css\" media=\"screen\">\
                       body {\
                           font-family: \"Helvetica Neue\",Helvetica,Arial,sans-serif;\
                           font-size: 1em;\
                           color: #CCC;\
                           background-color: #000;\
                           margin: 0;\
                       }\
                       #timer {\
                           text-align: right;\
                           font-size: 2em;\
                           color: #C679FF;\
                           font-weight: bold;\
                           margin-right: 5px;\
                       }\
                       #splits_container {\
                           overflow: auto;\
                       }\
                       #splits_container::-webkit-scrollbar {\
                           display: none;\
                       }\
                       #splits {\
                           width: 100%;\
                           border-spacing: 0;\
                       }\
                       #splits td {\
                           margin: 0;\
                           border-bottom: 1px solid #000;\
                           border-top: 1px solid #000;\
                       }\
                       .split_name {\
                           padding-left: 5px;\
                       }\
                       .split_time {\
                           text-align: right;\
                           padding-right: 5px;\
                       }\
                       .split_time.minus {\
                           color: #00BFFF;\
                       }\
                       .split_time.plus {\
                           color: #FF4000;\
                       }\
                       #splits .current_split td {\
                           border-bottom: 1px solid #1165B5;\
                           border-top: 1px solid #1165B5;\
                           color: #FFF;\
                       }\
                       </style>\
                       </head>\
                        <body bgcolor=\"black\">\
                           <div id=\"splits_container\">\
                           <table id=\"splits\"></table>\
                           </div>\
                           <div id=\"timer\"></div>\
                        </body>\
                        </html>"
                       );
}

std::shared_ptr<Timer> CoreApplication::timer() {
    return _timer;
}

void CoreApplication::LoadSplits(std::string file) {
    
}

void CoreApplication::SaveSplits(std::string file) {
    
}

void CoreApplication::LoadWSplitSplits(std::string file) {
    
    std::string line = "";
    std::ifstream file_stream;
    std::string title_equals = "Title=";
    std::string attempts_equals = "Attempts=";
    std::string size_equals = "Size=";
    std::string offset_equals = "Offset=";
    std::string icons_equals = "Icons=";
    
    file_stream.open(file);
    
    int i = 0;
    while (!file_stream.eof())
    {
        getline(file_stream, line);

        // Remove \r from end of line.
        line = line.substr(0, line.size() - 1);

        // Skip empty lines.
        if(line.size() > 0) {
            std::cout << line << std::endl;
            
            if(StartsWith(line, title_equals)) {
                std::string title = line.substr(title_equals.size(), line.size() - title_equals.size());
            } else if(StartsWith(line, attempts_equals)) {
                std::string attempts = line.substr(attempts_equals.size(), line.size() - attempts_equals.size());
            } else if(StartsWith(line, size_equals)) {
                std::string size = line.substr(size_equals.size(), line.size() - size_equals.size());
            } else if(StartsWith(line, offset_equals)) {
                std::string offset = line.substr(offset_equals.size(), line.size() - offset_equals.size());
            } else if(StartsWith(line, icons_equals)) {
                
            } else {
                // Split
                std::vector<std::string> split_values = SplitString(line, ',');
                std::cout << split_values[0] << std::endl;
                
                std::shared_ptr<Split> split(new Split);
                split->set_name(split_values[0]);
                double split_seconds = atof(split_values[2].c_str());
                unsigned long milliseconds = split_seconds * 1000;
                split->set_time(milliseconds);
                _splits.push_back(split);
            }
        }
        
        i++;
    }
    
    file_stream.close();
    ReloadSplits();
}

void CoreApplication::SaveWSplitSplits(std::string file) {
    
}

void CoreApplication::StartTimer() {
    _timer->Start();
}

void CoreApplication::StopTimer() {
    _timer->Stop();
}

void CoreApplication::ResetTimer() {
    _timer->Reset();
    _currentSplitIndex = 0;
    UpdateSplits();
}

void CoreApplication::SplitTimer() {
    if(_splits.size() == 0) {
        StopTimer();
        UpdateSplits();
    }
    if(_currentSplitIndex < _splits.size()) {
        _splits[_currentSplitIndex]->set_new_time(_timer->GetTimeElapsedMilliseconds());
        _currentSplitIndex++;
        if(_currentSplitIndex == _splits.size()) {
            StopTimer();
        }
        UpdateSplits();
    }
}

void CoreApplication::PauseTimer() {
    
}

void CoreApplication::ResumeTimer() {
    
}

void CoreApplication::GoToNextSegment() {
    if(CanGoToNextSegment()) {
        _splits[_currentSplitIndex]->set_skipped(true);
        _currentSplitIndex++;
        UpdateSplits();
    }
}

void CoreApplication::GoToPreviousSegment() {
    if(CanGoToPreviousSegment()) {
        _currentSplitIndex--;
        _splits[_currentSplitIndex]->set_skipped(false);
        UpdateSplits();
        if(_timer->status() == kFinished) {
            // Start the timer again if they go to the previous segment after finishing.
            _timer->Resume();
        }
    }
}

void CoreApplication::ChangeSetting(std::string key, std::string value) {
    
}

std::string CoreApplication::DisplayMilliseconds(unsigned long milliseconds, bool includeMilliseconds) {
    int hours = milliseconds / (1000*60*60);
    int mins = (milliseconds % (1000*60*60)) / (1000*60);
    int seconds = ((milliseconds % (1000*60*60)) % (1000*60)) / 1000;
    int millis_remaining = ((milliseconds % (1000*60*60)) % (1000*60)) % 1000;
    
    std::stringstream ss;
    ss << std::setfill('0');
    if(hours > 0) {
        ss << hours << ":";
    }
    if(hours == 0 && mins > 0) {
        ss << mins << ":";
    } else if(hours > 0) {
        ss << std::setw(2) << mins << ":";
    }
    if(hours == 0 && mins == 0) {
        ss << seconds;
    } else {
        ss << std::setw(2) << seconds;
    }
    if(includeMilliseconds) {
        ss << "." << std::setw(3) << millis_remaining;
    }

    return ss.str();
}

void CoreApplication::Update() {
    unsigned long elapsed = _timer->GetTimeElapsedMilliseconds();
    std::stringstream javascript_ss;
    javascript_ss << "$('#timer').text('" << DisplayMilliseconds(elapsed, true) << "');";
    
    if(_currentSplitIndex < _splits.size()) {
        if(_splits[_currentSplitIndex]->time() < elapsed) {
            unsigned long total = elapsed - _splits[_currentSplitIndex]->time();
            javascript_ss << "$('.current_split .split_time').text('+" << DisplayMilliseconds(total, false) << "').addClass('plus');";
        }
    }
    
    _browser->RunJavascript(javascript_ss.str());
}

void CoreApplication::ReloadSplits() {
    std::stringstream javascript_ss;

    std::string html = "";
    for(int i = 0; i < _splits.size(); i++) {
        html += "<tr><td class=\"split_name\">";
        html += _splits[i]->name();
        html += "</td><td class=\"split_time\">";
        html += DisplayMilliseconds(_splits[i]->time(), false);
        html += "</td></tr>";
    }
    
    javascript_ss << "document.getElementById('splits').innerHTML = '";
    javascript_ss << html;
    javascript_ss << "';";
    
    _browser->RunJavascript(javascript_ss.str());
    
    _currentSplitIndex = 0;
    UpdateSplits();
}

void CoreApplication::UpdateSplits() {
    // Update current split class.
    std::stringstream javascript_ss;
    javascript_ss << "$('#splits tr').removeClass('current_split').eq(" << _currentSplitIndex << ").addClass('current_split');";
    for(int i = 0; i < _currentSplitIndex; i++) {
        unsigned long old_time = _splits[i]->time();
        unsigned long new_time = _splits[i]->new_time();
        if(_splits[i]->skipped()) {
            javascript_ss << "$('#splits td.split_time:eq(" << i << ")').text('-').removeClass('minus').removeClass('plus');";
        } else if(old_time > new_time) {
            // Negative
            unsigned long total = old_time - new_time;
            javascript_ss << "$('#splits td.split_time:eq(" << i << ")').text('-" << DisplayMilliseconds(total, false) << "');";
            javascript_ss << "$('#splits td.split_time:eq(" << i << ")').addClass('minus');";
        } else {
            unsigned long total = new_time - old_time;
            javascript_ss << "$('#splits td.split_time:eq(" << i << ")').text('+" << DisplayMilliseconds(total, false) << "');";
            javascript_ss << "$('#splits td.split_time:eq(" << i << ")').addClass('plus');";
        }
    }
    for(int i = _currentSplitIndex; i < _splits.size(); i++) {
        std::cout << "Fixing Split: " << i << std::endl;
        javascript_ss << "$('#splits td.split_time:eq(" << i << ")').text('" << DisplayMilliseconds(_splits[i]->time(), false) << "').removeClass('minus').removeClass('plus');";
    }
    _browser->RunJavascript(javascript_ss.str());
}
bool CoreApplication::CanStart() {
    return _timer->status() != kRunning && _timer->status() != kFinished;
}

bool CoreApplication::CanPause() {
    return _timer->status() == kRunning;
}

bool CoreApplication::CanSplit() {
    return _timer->status() == kRunning;
}

bool CoreApplication::CanReset() {
    return _timer->status() != kInitial;
}

bool CoreApplication::CanGoToNextSegment() {
    return _timer->status() != kFinished && _currentSplitIndex + 1 < _splits.size();
}

bool CoreApplication::CanGoToPreviousSegment() {
    return _currentSplitIndex > 0;
}