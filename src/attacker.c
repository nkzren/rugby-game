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
direction_t invert_dir_up_down_right(direction_t curr_direction);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  static int turn = 0;
  static direction_t direction = (direction_t) DIR_DOWN_RIGHT;
  static position_t previous_position = INVALID_POSITION;
  static int collision_count = 0;
  static int zig_zag_count = 0;
  static int to_avoid_i = -1;

  turn++;

  if(turn == 3) {
    to_avoid_i = get_spy_position(defender_spy).i;
  }

  if (equal_positions(attacker_position, previous_position)) {
    
    collision_count++;
    
    if(collision_count % 4 == 1) {
      direction = invert_dir_up_down_right(direction);
    }

    else if(collision_count % 4 == 2)
      direction = (direction_t) DIR_RIGHT;
      
    else if(collision_count % 4 == 3)
      direction = (direction_t) DIR_UP;

    else if(collision_count % 4 == 0)
      direction = (direction_t) DIR_DOWN;
  }

  else {
    collision_count = 0;
    zig_zag_count++;

    if(to_avoid_i != -1 && attacker_position.i >= to_avoid_i)
      direction = (direction_t) DIR_DOWN_RIGHT;

    else if(to_avoid_i != -1 && attacker_position.i <= to_avoid_i)
      direction = (direction_t) DIR_UP_RIGHT;

    else if(zig_zag_count == 2) {
      direction = invert_dir_up_down_right(direction);
      zig_zag_count = 0;
    }
  }

  previous_position = attacker_position;
  
  return direction;
}

bool attacker_equals_directions(direction_t curr_dir, direction_t compar_dir) {
  return curr_dir.i == compar_dir.i && curr_dir.j == compar_dir.j;
}

direction_t invert_dir_up_down_right(direction_t curr_direction) {
  if(attacker_equals_directions(curr_direction, (direction_t) DIR_DOWN_RIGHT))
        return (direction_t) DIR_UP_RIGHT;

  else if(attacker_equals_directions(curr_direction, (direction_t) DIR_UP_RIGHT))
    return (direction_t) DIR_DOWN_RIGHT;

  return curr_direction;
}

/*----------------------------------------------------------------------------*/
