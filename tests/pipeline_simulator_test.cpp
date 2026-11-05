#include "pipeline_simulator.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {

    PipelineSimulator simulator;

    //Test 1: Three Instructions
    std::vector<std::string> instructions = {
        "I1",
         "I2",
         "I3"
    };

    std::vector<PipelineCycle> schedule = simulator.simulate(instructions);

    simulator.printSchedule(schedule);
    
    std::cout<<"Instructions: "<<instructions.size()<<'\n';
    std::cout<<"Generated Cycles: "<<schedule.size()<<'\n';
    //Exactly 7 cycles expected
    assert(schedule.size() == 7);

    //Test2 : First instruction enters IF in cycle 1
    assert(schedule[0].IF == "I1");

    //Test3 : First instruction reaches EX in cycle 3
    assert(schedule[2].EX == "I1");

    //Test4 : Third instruction reaches WB in cycle 7
    assert(schedule[6].WB == "I3");

    //Test5 : Empty input
    std::vector<std::string> emptyInstructions;

    std::vector<PipelineCycle> emptySchedule = simulator.simulate(emptyInstructions);

    assert(emptySchedule.empty());

    std::cout<<"All Pipeline Simulator tests passed!\n";

    return 0;
}