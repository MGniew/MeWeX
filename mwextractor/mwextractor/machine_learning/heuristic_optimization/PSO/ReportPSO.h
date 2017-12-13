#pragma once

#include "../BaseReport.h"
#include "../Point.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace particle_swarm_optimization
		{


/**
* The reporting class template for hill climbing algorithm. Report is saved in text file format.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType A time data type.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam NeighbourhoodType	A neighbourhood class.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType,
         typename TimeType,
         typename StepType>
class ReportPSO : public BaseReport
{
public:
    /**
    * Creates report with "report.txt" output file name.
    */
    ReportPSO(void) : BaseReport()
    {}

    /**
    * Creates report with output file name returned by rArgs.getReportFileName() and target name returned by rArgs.getTargetName().
    *
    * @param[in] rArgs Argument object.
    */
    ReportPSO(const ArgumentsType& rArgs) : BaseReport(rArgs.getReportFileName(), rArgs.getTargetName())
    {}

    /**
    * An object destructor. Closes report file.
    */
    ~ReportPSO(void)
    {}

    /**
    * Reports single step of the algorithm.
    *
    * @param[in] step			The number of the step.
    * @param[in] rCandidate		The candidate to <code>rCurrent</code>. The Best point in
    *							<code>rNeighbourhood</code>.
    * @param[in] rCurrent		The local best point.
    * @param[in] rBest			The best found point.
    * @param[in] rNeighbourhood	The neighbourhood of <code>rCurrent</code>.
    */
    void reportStep(StepType step, const Point& rCurrent, const Point& rBest)
    {
        this->mReport<<step;
        this->mReport<<":"<<std::endl;
        this->mReport<<"\tCurrent=";
        this->mReport<<rCurrent.toString();
        this->mReport<<","<<std::endl;
        this->mReport<<"\tBest=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;
    }
}; // class ReportPSO


		}// namespace particle_swarm_optimization
	} // namespace heuristic_optimization
} // namespace machine_learning
