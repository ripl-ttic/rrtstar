// file: test_rrtstar.c
//
// script to send lcm messages for sim obs and goal.

#include <stdio.h>
#include <lcm/lcm.h>

#include <lcmtypes/bot_core.h>
#include <lcmtypes/hr_lcmtypes.h>
     
static void
send_obs_message(lcm_t * lcm)
{
    erlcm_rect_list_t my_sim_obs;
    my_sim_obs.utime = 0; 

    my_sim_obs.xy[0] = 0;
    my_sim_obs.xy[1] = 0;

    my_sim_obs.num_rects = 2;
    
    erlcm_rect_t *rects = (erlcm_rect_t*)calloc(2, sizeof(erlcm_rect_t));
    rects[0].size[0] = 3;
    rects[0].size[1] = 3;
    rects[0].dxy[0] = -2;
    rects[0].dxy[1] = 3;
    rects[1].size[0] = 2;
    rects[1].size[1] = 2;
    rects[1].dxy[0] = -5;
    rects[1].dxy[1] = 5;
    /*rects[2].size[0] = 5;
    rects[2].size[1] = 5;
    rects[2].dxy[0] = 5;
    rects[2].dxy[1] = 5;
    */
    my_sim_obs.rects = rects;
    
    erlcm_rect_list_t_publish(lcm, "SIM_RECTS", &my_sim_obs);
    free(rects);
    return;
}
     
static void
send_goal_message(lcm_t * lcm)
{
  
    erlcm_goal_list_t my_goals;
    my_goals.num_goals = 1;

    erlcm_goal_t *goal  = (erlcm_goal_t*)calloc(1, sizeof(erlcm_goal_t));
    goal[0].pos[0] = -8; 
    goal[0].pos[1] = 3;
    goal[0].size[0] = 3;
    goal[0].size[1] = 3;
    my_goals.goals = goal;
    erlcm_goal_list_t_publish(lcm, "GOALS", &my_goals);
    free(goal);
    return;
}

int
main(int argc, char ** argv)
{
    lcm_t * lcm;

    lcm = lcm_create(NULL);
    if(!lcm)
        return 1;

    send_goal_message(lcm);

    //lcm_destroy(lcm);

    send_obs_message(lcm);

    lcm_destroy(lcm);
    return 0;
}