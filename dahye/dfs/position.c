//
//  position.c
//  maze
//
//  Created by dahye Jeong on 2018. 5. 7..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "position.h"

// 북동남서방향으로 이동하는 것이다. 세로가 X, 가로가 Y
int offset[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

Position move_to(Position pos,int dir){
    Position next;
    next.x = pos.x + offset[dir][0];
    next.y = pos.y + offset[dir][1];
    return next;
}
