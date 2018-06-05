#ifndef position_h
#define position_h

typedef struct pos {
	int x, y;
}Position;

Position move_to(Position pos, int dir);

#endif /* position_h */