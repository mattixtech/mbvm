//
//  system.h
//  mbvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//
#include <stdint.h>
#ifndef SYSTEM_H
#define SYSTEM_H

void exec(uint32_t programCode);
void dump_state();

#endif