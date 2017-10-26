#pragma once

#include <vector>
#include <string>

#include "BaseParameter.h"
#include "IntParameter.h"
#include "DoubleParameter.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


class ParameterFactory
{
public:
    ParameterFactory(void);
    ~ParameterFactory(void);

    static BaseParameter* create(int type, const std::string& rName,
                                 const std::string& rMin,
                                 const std::string& rMax,
                                 const std::string& rDefault,
                                 const std::string& rStep);
}; // class ParameterFactory


	}
}
