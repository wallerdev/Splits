//
//  AppDelegate.h
//  Splits
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <WebKit/WebKit.h>
#include <SplitsCore/CoreApplication.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet WebView *webView;
@property (assign) IBOutlet NSMenuItem *startMenuItem;
@property (assign) IBOutlet NSMenuItem *pauseMenuItem;
@property (assign) IBOutlet NSMenuItem *splitMenuItem;
@property (assign) IBOutlet NSMenuItem *resetMenuItem;
@property (assign) IBOutlet NSMenuItem *previousSegmentMenuItem;
@property (assign) IBOutlet NSMenuItem *nextSegmentMenuItem;
- (IBAction)timerStart:(id)sender;
- (IBAction)timerSplit:(id)sender;
- (IBAction)openDocument:(id)sender;
- (IBAction)timerReset:(id)sender;
- (IBAction)timerPause:(id)sender;
- (IBAction)timerPreviousSegment:(id)sender;
- (IBAction)timerNextSegment:(id)sender;

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem;

@end

CoreApplication *_core_application;