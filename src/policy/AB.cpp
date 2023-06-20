#include <cstdlib>

#include "../state/state.hpp"
#include "./AB.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int alphabeta(State *now, int depth, bool maximizingPlayer, int alpha, int beta){
    if(!now->legal_actions.size())
    now->get_legal_actions();
    if(depth == 0 || now->legal_actions.size() == 0){
        return now->evaluate();
    }
    auto actions = now->legal_actions;
    if(maximizingPlayer){
        //int value = -1000;
        for(auto child : actions){
            State *childState = now->next_state(child);
            int temp = alphabeta(childState, depth-1, 0, alpha, beta);
            if(temp > alpha){
                alpha = temp;
            }
            if(alpha >= beta){
                break;
            }
        }
        return alpha;
    }
    else{
        //int value = 1000;
        for(auto child : actions){
            State *childState = now->next_state(child);
            int temp = alphabeta(childState, depth-1, 1, alpha, beta);
            if(temp < beta){
                beta = temp;
            }
            if(alpha >= beta){
                break;
            }
        }
        return beta;
    }
}
Move ab::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

    Move move;
    int alpha = -1000;
    int beta = 1000;
    auto actions = state->legal_actions;

    if(!state->player){
        int value = -1000;
        for(auto child : actions){
            State *childState = state->next_state(child);
            int temp = alphabeta(childState, depth-1, 0, alpha, beta);
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
            int temp = alphabeta(childState, depth-1, 1, alpha, beta);
            if(temp < value){
                value = temp;
                move = child;
            }
        }
    }
    return move;
}
