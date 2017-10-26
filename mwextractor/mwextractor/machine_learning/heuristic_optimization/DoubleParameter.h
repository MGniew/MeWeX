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
/**
*
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class DoubleParameter : protected TParameter<double>, public BaseParameter
{
public:
    DoubleParameter(void);
    DoubleParameter(const std::string& rName,
                    const std::vector<double>& rMin,
                    const std::vector<double>& rMax,
                    const std::vector<double>& rParameter,
                    const std::vector<double>& rStep);

    DoubleParameter(const DoubleParameter& rParameter);

    DoubleParameter& operator=(const DoubleParameter& rParameter);

    ~DoubleParameter(void) throw();

    virtual BaseParameter* duplicate(void) const;
    virtual void setRandomValue(unsigned int index);
    virtual bool isEqual(const BaseParameter& rParameter);
    virtual std::string getName(void);
    virtual Data getValueAt(unsigned int index);
    void setValueAt(unsigned int index, const Data& rData);
    unsigned int getSize(void) const;
    virtual std::string toString(void);
}; // class DoubleParameter


	}
} // namespace Optimizer

