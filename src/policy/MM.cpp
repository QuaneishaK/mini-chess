#include <cstdlib>

#include "../state/state.hpp"
#include "./MM.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int minimax(State *now, int depth, bool maximizingPlayer){
    if(!now->legal_actions.size())
    now->get_legal_actions();
    if(depth == 0 || now->legal_actions.size() == 0){
        return now->evaluate();
    }
    auto actions = now->legal_actions;
    if(maximizingPlayer){
        int value = -1000;
        for(auto child : actions){
            State *childState = now->next_state(child);
            int temp = minimax(childState, depth-1, 0);
            if(temp > value){
                value = temp;
            }
        }
        return value;
    }
    else{
        int value = 1000;
        for(auto child : actions){
            State *childState = now->next_state(child);
            int temp = minimax(childState, depth-1, 1);
            if(temp < value){
                value = temp;
            }
        }
        return value;
    }
}
Move mm::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

    Move move;
    auto actions = state->legal_actions;

    if(!state->player){
        int value = -1000;
        for(auto child : actions){
            State *childState = state->next_state(child);
            int temp = minimax(childState, depth-1, 0);
            if(temp > value){
                value = temp;
                move = child;
            }
        }
    }
    else{
        int value = 1000;
        for(auto child : actions){
            State *childState = state->next_state(child);
            int temp = minimax(childState, depth-1, 1);
            if(temp < value){
                value = temp;
                move = child;
            }
        }
    }
    return move;
}
