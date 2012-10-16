//
//  AppDelegate.h
//  Splits
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#include <SplitsCore/timer.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet WebView *web_view;

@end

Timer *_timer;