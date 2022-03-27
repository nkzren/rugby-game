// Standard headers
#include <stdio.h>
#include <stdbool.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Internal functions
bool defender_equals_directions(direction_t curr_dir, direction_t compar_dir);
direction_t first_two_turns_strategy(position_t defender_position, position_t previous_position, direction_t direction);
direction_t other_turns_strategy(position_t defender_position, position_t previous_position, direction_t direction, int center_i, int trashold);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  static int turn = 0;
  static int center_i = -1;
  static direction_t direction = (direction_t) DIR_UP_LEFT;
  static position_t previous_position = INVALID_POSITION;

  turn++;

  if(turn == 1 || turn == 2) {
    center_i = defender_position.i;
    direction = first_two_turns_strategy(defender_position, previous_position, direction);
  }
  
  if(turn == 3)
    center_i = get_spy_position(attacker_spy).i;

  if(turn >= 3)
    direction = other_turns_strategy(defender_position, previous_position, direction, center_i, 2);

  return direction;
}

bool defender_equals_directions(direction_t curr_dir, direction_t compar_dir) {
  return curr_dir.i == compar_dir.i && curr_dir.j == compar_dir.j;
}

direction_t first_two_turns_strategy(position_t defender_position, position_t previous_position, direction_t direction) {

  direction_t new_direction = direction;

  if (equal_positions(defender_position, previous_position)) {
    if(defender_equals_directions(direction, (direction_t) DIR_UP_LEFT))
      new_direction = (direction_t) DIR_DOWN_LEFT;

    else if(defender_equals_directions(direction, (direction_t) DIR_DOWN_LEFT))
      new_direction = (direction_t) DIR_UP_LEFT;
  }

  previous_position = defender_position;

  return new_direction;
}

direction_t other_turns_strategy(position_t defender_position, position_t previous_position, direction_t direction, int center_i, int trashold) {

  static int collision_count = 0;

  direction_t new_direction = direction;

  if(defender_equals_directions(direction, (direction_t) DIR_UP_LEFT))
      new_direction = (direction_t) DIR_UP;

  else if(defender_equals_directions(direction, (direction_t) DIR_DOWN_LEFT))
    new_direction = (direction_t) DIR_DOWN;

  if (equal_positions(defender_position, previous_position)) {

    collision_count++;
    
    if(defender_equals_directions(direction, (direction_t) DIR_UP))
      new_direction = (direction_t) DIR_DOWN;

    else if(defender_equals_directions(direction, (direction_t) DIR_DOWN))
      new_direction = (direction_t) DIR_UP;

    if(collision_count == 2)
      new_direction = (direction_t) DIR_RIGHT;
  }

  else {

    collision_count = 0;
    
    if(defender_position.i >= center_i + trashold)
      new_direction = (direction_t) DIR_UP;
  
    if(defender_position.i <= center_i - trashold)
      new_direction = (direction_t) DIR_DOWN;
  }

  return new_direction;
}

/*----------------------------------------------------------------------------*/
