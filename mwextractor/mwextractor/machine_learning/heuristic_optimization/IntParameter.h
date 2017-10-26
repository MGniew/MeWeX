#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "Optimizer.h"
#include "TParameter.h"
#include "BaseParameter.h"
#include "Random.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{


class IntParameter : protected TParameter<int>, public BaseParameter
{
public:
    IntParameter(void);
    IntParameter(const std::string& rName,
                 const std::vector<int>& rMin,
                 const std::vector<int>& rMax,
                 const std::vector<int>& rParameter,
                 const std::vector<int>& rStep);

    IntParameter(const IntParameter& rParameter);

    IntParameter& operator=(const IntParameter& rParameter);

    ~IntParameter(void) throw();

    virtual BaseParameter* duplicate(void) const;
    virtual void setRandomValue(unsigned int index);
    virtual bool isEqual(const BaseParameter& rParameter);
    virtual std::string getName(void);
    virtual Data getValueAt(unsigned int index);
    virtual void setValueAt(unsigned int index, const Data& rData);
    virtual unsigned int getSize(void) const;
    virtual std::string toString(void);
}; // class IntParameter


	}
} // namespace Optimizer


