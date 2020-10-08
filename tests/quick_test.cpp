//
// Created by theom on 10/8/2020.
//

#include <simulations/langtons_ant/EdgeBehavior.hpp>
#include <iostream>

using std::cout;
using std::endl;

int main() {
    EdgeBehavior *testEdge = new Teleport(new MoveBehavior());
    std::vector<std::pair<int, int>> testPos;
    for (int i = 0; i < 15; ++i) {
        testPos.emplace_back(3*i, 5*i);
        cout<<i*3<<" "<<i*5<<endl;
    }
    testEdge->adjustPositions(testPos);
    for(auto i: testPos){
        cout<<i.first<<" "<<i.second<<endl;
    }

    return 0;
}