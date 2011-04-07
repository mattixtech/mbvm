//
//  system.c
//  mbhvm
//
//  Created by Matthew Brooks on 11-04-07.
//  Copyright 2011 Megabit. All rights reserved.
//

#include "system.h"
#include "vm.h"
#include <stdio.h>

void exec(unsigned int programCode){
    printf("%u",programCode);
    pc+=1;
}