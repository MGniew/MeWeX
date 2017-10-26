#pragma once

#include "../BaseReport.h"
#include "../Point.h"

namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace RandomSearch
		{


/**
* The reporting class template for random search algorithm. Report is saved in text file format.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType A time data type.
* @tparam StepType A algorithm step type. Could be int, double, etc.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename TimeType,
         typename StepType>
class ReportRS : public BaseReport
{
public:
    /**
    * Creates report with "report.txt" output file name.
    */
    ReportRS(void) : BaseReport()
    {}

    /**
    * Creates report with output file name returned by rArgs.getReportFileName() and target name returned by rArgs.getTargetName().
    *
    * @param[in] rArgs Argument object.
    */
    ReportRS(const ArgumentsType& rArgs) : BaseReport(rArgs.getReportFileName(), rArgs.getTargetName())
    {}

    /**
    * An object destructor. Closes report file.
    */
    ~ReportRS(void)
    {}

    /**
    * Reports single step of the algorithm.
    *
    * @param[in] step The number of the step.
    * @param[in] rCandidate The current point. The candidate to <code>rBest</code>.
    * @param[in] rBest The best found point.
    */
    void reportStep(StepType step, Point& rCandidate, Point& rBest)
    {
        this->mReport<<step;
        this->mReport<<":"<<std::endl;
        this->mReport<<"\tCandidate=";
        this->mReport<<rCandidate.toString();
        this->mReport<<","<<std::endl;
        this->mReport<<"\tBest=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;
    }
}; // class ReportRS


		}
	} // namespace RandomSearch
} // namespace Optimizer
