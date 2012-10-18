//
//  CoreApplication.h
//  SplitsCore
//
//  Created by Edward Waller on 10/17/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#ifndef __SplitsCore__CoreApplication__
#define __SplitsCore__CoreApplication__

#include <iostream>
#include "WebBrowserInterface.h"
#include "timer.h"

class CoreApplication
{
public:
    CoreApplication(std::shared_ptr<WebBrowserInterface> browser, std::string settings_file);
    void LoadSplits(std::string file);
    void SaveSplits(std::string file);
    void StartTimer();
    void StopTimer();
    void ResetTimer();
    void ChangeSetting(std::string key, std::string value);
    void Update();
private:
    std::shared_ptr<WebBrowserInterface> _browser;
    std::string _settings_file;
    Timer _timer;
};

#endif /* defined(__SplitsCore__CoreApplication__) */
