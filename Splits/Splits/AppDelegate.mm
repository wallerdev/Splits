//
//  AppDelegate.m
//  Splits
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#import "AppDelegate.h"
#import <WebKit/WebKit.h>
#include <SplitsCore/WebBrowserInterface.h>
#include "Browser.h"

@implementation AppDelegate

@synthesize web_view;

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    std::shared_ptr<WebBrowserInterface> browser_interface(new Browser(web_view));
    _core_application = new CoreApplication(browser_interface, "");
    
    
    
    [NSTimer scheduledTimerWithTimeInterval: 0.033
                                                  target: self
                                                selector:@selector(onTick:)
                                                userInfo: nil repeats:YES];
}

-(void)onTick:(NSTimer *)timer {
    _core_application->Update();
}

- (void)webView:(WebView *)sender didFinishLoadForFrame:(WebFrame *)frame {
    _core_application->LoadWSplitSplits("/Users/Eddie/Desktop/New Super Mario Bros Wii PB");
}

- (IBAction)timerStart:(id)sender {
    _core_application->StartTimer();
}

- (IBAction)timerSplit:(id)sender {
    _core_application->SplitTimer();
}
@end
