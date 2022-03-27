// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Internal functions
bool attacker_equals_directions(direction_t curr_dir, direction_t compar_dir);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  static int turn = 0;
  static direction_t direction = (direction_t) DIR_DOWN_RIGHT;
  static position_t previous_position = INVALID_POSITION;
  static int collision_count = 0;

  if (equal_positions(attacker_position, previous_position)) {
    collision_count++;
    
    if(collision_count == 1) {
      if(attacker_equals_directions(direction, (direction_t) DIR_DOWN_RIGHT))
        direction = (direction_t) DIR_UP_RIGHT;

      else if(attacker_equals_directions(direction, (direction_t) DIR_UP_RIGHT))
        direction = (direction_t) DIR_DOWN_RIGHT;
    }

    else if(collision_count == 2)
      direction = (direction_t) DIR_RIGHT;
      
    else if(collision_count == 3)
      direction = (direction_t) DIR_UP;

    else if(collision_count == 4)
      direction = (direction_t) DIR_DOWN;
  }

  else {
    collision_count = 0;

    if(attacker_equals_directions(direction, (direction_t) DIR_DOWN_RIGHT))
      direction = (direction_t) DIR_UP_RIGHT;

    else if(attacker_equals_directions(direction, (direction_t) DIR_UP_RIGHT))
      direction = (direction_t) DIR_DOWN_RIGHT;
  }
  
  return direction;
}

bool attacker_equals_directions(direction_t curr_dir, direction_t compar_dir) {
  return curr_dir.i == compar_dir.i && curr_dir.j == compar_dir.j;
}

/*----------------------------------------------------------------------------*/
