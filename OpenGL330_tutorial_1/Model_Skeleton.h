#include "Collision_Box.h"
class Model_Skeleton{
public:
	//virtual int check_collision(Collision_Box*) = 0;
	virtual void draw(void) = 0;
	virtual void move_collision_box() = 0;
	virtual void update(void) = 0;
	virtual int check_collision(Collision_Box*) = 0;
	virtual void create_collision_box(void) = 0;
private:
};