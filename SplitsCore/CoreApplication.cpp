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

CoreApplication::CoreApplication(std::shared_ptr<WebBrowserInterface> browser, std::string settings_file) : _browser(browser), _settings_file(settings_file) {
    _browser->LoadHTML("<html>\
                       <style type=\"text/css\" media=\"screen\">\
                       body {\
                           font-family: \"Helvetica Neue\",Helvetica,Arial,sans-serif;\
                           font-size: 10px;\
                           color: #FFF;\
                           background-color: #000;\
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
                       .split_time {\
                           text-align: right;\
                       }\
                       #splits .current_split td {\
                           border-bottom: 1px solid #0A6AC2;\
                           border-top: 1px solid #0A6AC2;\
                       }\
                       </style>\
                        <body bgcolor=\"black\">\
                           <table id=\"splits\"></table>\
                           <h1 id=\"timer\" style=\"color: lightgreen; font-family: Helvetica Neue; \"></h1>\
                        </body>\
                        </html>"
                       );
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


//    Title=New Super Mario Bros Wii 100%
//    Attempts=72
//    Offset=0
//    Size=143,25
//    1-T,463,468.12,478.39
//    1-C,954,913.68,433.56
//    2-T,1268,1232.56,287.8
//    2-C,1981,1913.08,680.52
//    3-T,2918,2845.21,912.51
//    3-C,3580,3518.51,632.3
//    4-T (Normal),4062,4002.51,484
//    4-C,4726,4657.1,654.59
//    5-T,5291,5178.88,548.15
//    5-C,6011,5912.56,688.68
//    6-T,6700,6573.97,661.41
//    6-C,7058,6921.39,347.42
//    7-T (Normal),8269,8016.82,1095.43
//    7-C,8899,8647.82,631
//    8-T,9704,9435.76,777.68
//    8-C,10691,10366.8,931.04
//    1-Cannon,0,10867.06,126.67
//    2-Cannon,0,11089.72,222.66
//    4-Cannon,0,11217.38,127.66
//    6-Cannon,0,11462.18,244.8
//    5-Cannon,12066,11703.09,240.91
//    World 9,13901.29,12997.62,915.6
//    Icons="","","","","","","","","","","","","","","","","","","","","",""
    RefreshSplits();
}

void CoreApplication::SaveWSplitSplits(std::string file) {
    
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
    javascript_ss << "document.getElementById('timer').innerText = '" << elapsed_time << "';";
    
    _browser->RunJavascript(javascript_ss.str());
}

void CoreApplication::RefreshSplits() {
    std::stringstream javascript_ss;

    std::string html = "";
    for(int i = 0; i < _splits.size(); i++) {
        html += "<tr><td class=\"split_name\">";
        html += _splits[i]->name();
        html += "</td><td class=\"split_time\">";
        
        unsigned long milliseconds = _splits[i]->time();
        
        int hours = milliseconds / (1000*60*60);
        int mins = (milliseconds % (1000*60*60)) / (1000*60);
        int seconds = ((milliseconds % (1000*60*60)) % (1000*60)) / 1000;
        
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
        
        html += ss.str();
        html += "</td></tr>";
    }
    
    javascript_ss << "document.getElementById('splits').innerHTML = '";
    javascript_ss << html;
    javascript_ss << "';";
    
    std::cout << javascript_ss.str() << std::endl;
    
    _browser->RunJavascript(javascript_ss.str());
    _browser->RunJavascript("document.getElementById('timer').style.color = 'red';");
    
}