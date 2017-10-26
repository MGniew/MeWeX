#pragma once

#include "../BaseReport.h"
#include "Individual.h"


namespace machine_learning
{
	namespace heuristic_optimization
	{
		namespace EvolutionaryAlgorithm
		{


/**
* The reporting class template for evolutionary algorithm. Report is saved in text file format.
*
* @tparam ArgumentsType A call policy argument type.
* @tparam TimeType A time data type.
* @tparam StepType A algorithm step type. Could be int, double, etc.
* @tparam PopulationType A poulation class.
*
* @author Lukasz Klyk <a href="mailto:klyk.lukasz@gmail.com">klyk.lukasz@gmail.com</a>
*/
template<typename ArgumentsType, typename TimeType, typename StepType, typename PopulationType>
class ReportEA : public BaseReport
{
public:
    /**
    * Creates report with "report.txt" output file name.
    */
    ReportEA(void) : BaseReport()
    {}

    /**
    * Creates report with output file name returned by rArgs.getReportFileName() and target name returned by rArgs.getTargetName().
    *
    * @param[in] rArgs Argument object.
    * @see BaseCallPoliciesArguments
    */
    ReportEA(const ArgumentsType& rArgs) : BaseReport(rArgs.getReportFileName(), rArgs.getTargetName())
    {}

    /**
    * An object destructor. Closes report file.
    */
    ~ReportEA(void)
    {}

    /**
    * Reports single step of the algorithm.
    *
    * @param[in] rStep The number of the step.
    * @param[in] rBest The best found individual.
    * @param[in] rPopulation The population object.
    */
    void reportStep(const StepType& rStep, const Individual& rBest, const PopulationType& rPopulation)
    {
        this->mReport<<rStep;
        this->mReport<<":"<<std::endl;
        this->mReport<<"\tBest=";
        this->mReport<<rBest.toString();
        this->mReport<<std::endl;
        this->mReport<<"\tPopulation=";
        this->mReport<<rPopulation.toString();
        this->mReport<<std::endl;
    }
}; // class ReportEA


		}
	} // namespace EvolutionaryAlgorithm
} // namespace Optimizer


