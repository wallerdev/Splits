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

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    std::shared_ptr<WebBrowserInterface> browser_interface(new Browser(web_view));
    _core_application = new CoreApplication(browser_interface, "");
    
    _core_application->StartTimer();
    
    
    
    NSTimer *t = [NSTimer scheduledTimerWithTimeInterval: 0.033
                                                  target: self
                                                selector:@selector(onTick:)
                                                userInfo: nil repeats:YES];
}

-(void)onTick:(NSTimer *)timer {
    _core_application->Update();
}

@end
