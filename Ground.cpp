#include "Player.h"
#include "Ground.h"

const int ground = 340;

Ground::Ground()
{

}

Ground::~Ground()
{
}

int Ground::GetCurrentGroundY(Position2f & pos) const
{
	return ground;
}
