//
//  maze.h
//  maze
//
//  Created by dahye Jeong on 2018. 5. 27..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef maze_h
#define maze_h
#define MAX 8
int maze[MAX+2][MAX+2]={
    {4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,0,0,1,1,0,0,4},
    {4,0,1,1,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,4},
    {4,0,1,1,1,0,1,0,0,4},
    {4,4,4,4,4,4,4,4,4,4}
};
int n=MAX+2; // 미로의 크기


#endif /* maze_h */
