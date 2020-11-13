/****************************************************************************************
 *
 ***************************************************************************************/
#include <simulations/langtons_ant/BehaviorFactory.hpp>

int main(){
    BehaviorFactory *bxFactory = BehaviorFactory::getInstance();
    Behaviors test = bxFactory->createBehaviors(TELEPORT, 1);
    int a = 5;

    return 0;
}