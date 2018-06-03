//
//  position.h
//  maze
//
//  Created by dahye Jeong on 2018. 5. 7..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef position_h
#define position_h

typedef struct pos{
    int x,y;
}Position;

Position move_to(Position pos, int dir);

#endif /* position_h */
