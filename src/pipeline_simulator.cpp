#include "pipeline_simulator.hpp"
#include <cstddef>
#include<iostream>
#include<iomanip>

std::vector<PipelineCycle> PipelineSimulator::simulate(
    const std::vector<std::string>& instructions
) 
const{
    //No instructions means no pipeline cycles
    
    if(instructions.empty()){
        return {};
    }

    //Five stages: IF, ID, EX, MEM, WB
    //Total Cycles = number of instructions + 4 
    
    std::vector<PipelineCycle> schedule(instructions.size() + 4);

    for(std::size_t i = 0; i < instructions.size(); ++i){
        schedule[i].IF = instructions[i];
        schedule[i + 1].ID = instructions[i];
        schedule[i + 2].EX = instructions[i];
        schedule[i + 3].MEM = instructions[i];
        schedule[i + 4].WB = instructions[i];
    }

    return schedule;
}

void PipelineSimulator::printSchedule(
    const std::vector<PipelineCycle>& schedule
        ) const{
            if(schedule.empty()) {
                std::cout<<"No instructions to display.\n";
                return;
            }

            //Print table header
            std::cout <<std::left
                      <<std::setw(10) << "Cycle"
                      <<std::setw(8) << "IF"
                      <<std::setw(8) << "ID"
                      <<std::setw(8) << "EX"
                      <<std::setw(8) << "MEM"
                      <<std::setw(8) << "WB"
                      <<'\n';
                
            std::cout<< std::string(50, '-') << '\n';

            //Print each pipeline cycle
            for(std::size_t i = 0; i < schedule.size(); ++i){
                const auto& cycle = schedule[i];

                std::cout <<std::setw(10) << i + 1
                          <<std::setw(8) << (cycle.IF.empty() ? "-" : cycle.IF)
                          <<std::setw(8) << (cycle.ID.empty() ? "-" : cycle.ID)
                          <<std::setw(8) << (cycle.EX.empty() ? "-" : cycle.EX)
                          <<std::setw(8) << (cycle.MEM.empty() ? "-" : cycle.MEM)
                          <<std::setw(8) << (cycle.WB.empty() ? "-" : cycle.WB)
                          <<'\n';
            }
}
