//
//  Browser.h
//  Splits
//
//  Created by Edward Waller on 10/17/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#ifndef __Splits__Browser__
#define __Splits__Browser__

#import <WebKit/WebKit.h>
#include <iostream>
#include <SplitsCore/WebBrowserInterface.h>

class Browser : public WebBrowserInterface {
public:
    Browser(WebView *web_view);
    void LoadHTML(std::string html);
    void RunJavascript(std::string javascript);
private:
    WebView *_web_view;
};

#endif /* defined(__Splits__Browser__) */