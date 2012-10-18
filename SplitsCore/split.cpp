//
//  split.cpp
//  SplitsCore
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#include "split.h"

Split::Split() {
    
}

Split::~Split() {
    
}

std::string Split::name() {
    return _name;
}

void Split::set_name(std::string name) {
    _name = name;
}

unsigned long Split::time() {
    return _time;
}

void Split::set_time(unsigned long time) {
    _time = time;
}