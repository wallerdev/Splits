//
//  AppDelegate.m
//  Splits
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#import "AppDelegate.h"
#import <WebKit/WebKit.h>

@implementation AppDelegate

@synthesize web_view;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    _timer = new Timer();
    _timer->Start();
    
    [[web_view mainFrame] loadHTMLString:[NSString stringWithFormat:@"<html>\
     <body bgcolor=\"black\">\
        <h1 id=\"timer\" style=\"color: lightgreen; font-family: Helvetica Neue; \"></h1>\
     </body>\
     </html>"] baseURL:nil];
    
    NSTimer *t = [NSTimer scheduledTimerWithTimeInterval: 0.033
                                                  target: self
                                                selector:@selector(onTick:)
                                                userInfo: nil repeats:YES];
}

-(void)onTick:(NSTimer *)timer {
    std::string elapsed_time = _timer->GetTimeElapsedDisplay();
    NSString *errorMessage = [NSString stringWithCString:elapsed_time.c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    [[web_view windowScriptObject] evaluateWebScript:[NSString stringWithFormat:@"document.getElementById('timer').innerText = '%@';", errorMessage]];
}

@end
