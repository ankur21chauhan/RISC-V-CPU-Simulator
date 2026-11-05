#ifndef PIPELINE_SIMULATOR_HPP
#define PIPELINE_SIMULATOR_HPP

#include <string>
#include <vector>

struct PipelineCycle{
    std::string IF;
    std::string ID;
    std::string EX;
    std::string MEM;
    std::string WB;
};

class PipelineSimulator{
public:
    std::vector<PipelineCycle> simulate(
        const std::vector<std::string>& instructions
    ) const;

    void printSchedule(
        const std::vector<PipelineCycle>& schedule
    ) const;
};

#endif