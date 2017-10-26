#pragma once

#include <string>
#include <fstream>

#include "Point.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{


/**
* BaseReport is the base reporting class. It is used to save the summary of optimization algorithm. A data is
* saved in text file format. BaseReport could be also a good base to define specialized report class for given
* algorithm.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
class BaseReport
{
public:
    /**
    * Creates BaseReport with "report.txt" file name.
    *
    * @exception std::ios_base::failure Thrown if report file could not be created.
    */
    BaseReport(void);

    /**
    * Creates BaseReport with specified output file name.
    *
    * @param[in] rFileName Output file name.
    * @param[in] rTargetName The name of the optimization task.
    *
    * @exception std::ios_base::failure Thrown if report file could not be created.
    */
    BaseReport(const std::string& rFileName, const std::string rTargetName);

    /**
    * An object destructor. Closes report file.
    */
    ~BaseReport(void) throw();

    /**
    * A standard report summary. Method is called at the end of each optimization algorithm.
    *
    * @tparam TimeType Time data type.
    *
    * @param[in] numberOfevaluations Total number of made evaluations.
    * @param[in] rTime Total working time.
    * @param[in] rBest The best found parameters feature. The result of algorithm.
    */
    template<typename TimeType>
    void reportSummary(int numberOfevaluations, const TimeType& rTime, const Point& rBest)
    {
        this->mReport<<"-------------------Summary-------------------";
        this->mReport<<std::endl;
        this->mReport<<"Number of evaluations=";
        this->mReport<<numberOfevaluations;
        this->mReport<<std::endl;
        this->mReport<<"Total time=";
        this->mReport<<rTime;
        this->mReport<<" seconds"<<std::endl;
        this->mReport<<"Best=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;
    }

protected:
    /**
    * The file report stream.
    */
    std::ofstream mReport;

    /**
    * The file report name.
    */
    std::string mFileName;
}; // class BaseReport


	}
} // namespace Optimizer
