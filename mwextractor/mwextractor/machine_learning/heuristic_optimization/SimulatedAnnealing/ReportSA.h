#pragma once

#include "../BaseReport.h"
#include "../Point.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace SimulatedAnnealing
		{


/**
* The reporting class template for simulated annealing algorithm. Report is saved in text file format.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType A time data type.
* @tparam TemperatureType A temperature data type. Could be int, double, etc.
* @tparam StepType A algorithm step type. Could be int, double, etc.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename TimeType, typename TemperatureType, typename StepType>
class ReportSA : public BaseReport
{
public:
    /**
    * Creates report with "report.txt" output file name.
    */
    ReportSA(void) : BaseReport()
    {}

    /**
    * Creates report with output file name returned by rArgs.getReportFileName() and target name returned by rArgs.getTargetName().
    *
    * @param[in] rArgs Argument object.
    */
    ReportSA(const ArgumentsType& rArgs) : BaseReport(rArgs.getReportFileName(), rArgs.getTargetName())
    {}

    /**
    * An object destructor. Closes report file.
    */
    ~ReportSA(void)
    {}

    /**
    * Reports single step of the algorithm.
    *
    * @param[in] step			The number of the step.
    * @param[in] rTemperature	The temperature in the given step.
    * @param[in] rCurrent		The current point. The candidate to <code>rBest</code>.
    * @param[in] rBest			The best found point.
    */
    void reportStep(StepType step, TemperatureType& rTemperature, const Point& rCurrent, const Point& rBest)
    {
        this->mReport<<step;
        this->mReport<<":"<<std::endl;
        this->mReport<<"\tTemperature=";
        this->mReport<<rTemperature;
        this->mReport<<","<<std::endl;
        this->mReport<<"\tCurrent=";
        this->mReport<<rCurrent.toString();
        this->mReport<<","<<std::endl;
        this->mReport<<"\tBest=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;
    }
}; // class ReportSA


		}
	} // namespace SimulatedAnnealing
} // namespace Optimizer


