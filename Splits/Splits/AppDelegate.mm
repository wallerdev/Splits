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

@synthesize webView;
@synthesize startMenuItem;

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    std::shared_ptr<WebBrowserInterface> browser_interface(new Browser(webView));
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

}

- (IBAction)timerStart:(id)sender {
    _core_application->StartTimer();
}

- (IBAction)timerSplit:(id)sender {
    _core_application->SplitTimer();
}

- (IBAction)openDocument:(id)sender {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setCanChooseDirectories:NO];
    
    if([openDlg runModal] == NSOKButton) {
        NSString *file = [[openDlg URL] path];
        _core_application->LoadWSplitSplits([file cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

- (IBAction)timerReset:(id)sender {
    _core_application->ResetTimer();
}

- (IBAction)timerPause:(id)sender {
    _core_application->PauseTimer();
}

- (IBAction)timerPreviousSegment:(id)sender {
}
- (IBAction)timerNextSegment:(id)sender {
}

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem {
    if([menuItem action] == @selector(timerStart:)) {
        return _core_application->CanStart();
    } else if([menuItem action] == @selector(timerPause:)) {
        return _core_application->CanPause();
    } else if([menuItem action] == @selector(timerSplit:)) {
        return _core_application->CanSplit();
    } else if([menuItem action] == @selector(timerReset:)) {
        return _core_application->CanReset();
    } else if([menuItem action] == @selector(timerPreviousSegment:)) {
        return _core_application->CanGoToPreviousSegment();
    } else if([menuItem action] == @selector(timerNextSegment:)) {
        return _core_application->CanGoToNextSegment();
    }
    return YES;
}
@end
