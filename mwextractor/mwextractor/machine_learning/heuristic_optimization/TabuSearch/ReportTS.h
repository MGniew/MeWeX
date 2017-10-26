#pragma once

#include "../BaseReport.h"
#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace TabuSearch
		{


/**
* The reporting class template for tabu search algorithm. Report is saved in text file format.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType A time data type.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam NeighbourhoodType A neighbourhood class.
* @tparam TabuListType A tabu list class.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename TimeType,
         typename StepType,
         typename NeighbourhoodType,
         typename TabuListType>
class ReportTS : public BaseReport
{
public:
    /**
    * Creates report with "report.txt" output file name.
    */
    ReportTS(void) : BaseReport()
    {}

    /**
    * Creates report with output file name returned by rArgs.getReportFileName() and target name returned by rArgs.getTargetName().
    *
    * @param[in] rArgs Argument object.
    */
    ReportTS(const ArgumentsType& rArgs) : BaseReport(rArgs.getReportFileName(), rArgs.getTargetName())
    {}

    /**
    * An object destructor. Closes report file.
    */
    ~ReportTS(void)
    {}

    /**
    * Reports single step of the algorithm.
    *
    * @param[in] step The number of the step.
    * @param[in] rCurrent The local best point.
    * @param[in] rBest The best found point.
    * @param[in] rNeighbourhood The neighbourhood of <code>rCurrent</code>.
    * @param[in] rTabuList The tabu list.
    */
    void reportStep(StepType step, Point& rCurrent, Point& rBest, NeighbourhoodType& rNeighbourhood, TabuListType& rTabuList)
    {
        this->mReport<<step;
        this->mReport<<":"<<std::endl;
        this->mReport<<"\tCurrent=";
        this->mReport<<rCurrent.toString();
        this->mReport<<","<<std::endl;
        this->mReport<<"\tBest=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;

        this->mReport<<"\tNeighbourhood=";
        this->mReport<<rNeighbourhood.toString();
        this->mReport<<std::endl;

        this->mReport<<"\tTabu List=";
        this->mReport<<rTabuList.toString();
        this->mReport<<std::endl;
    }
}; // class ReportTS


		}
	} // namespace TabuSearch
} // namespace Optimizer
