
#include "filter/Not.h"
#include "filter/Or.h"
#include "filter/And.h"
#include "filter/Xor.h"
#include "filter/Frequency.h"
#include "filter/CorporaFrequency.h"
#include "filter/Relation.h"
#include "filter/EveryWord.h"
#include "filter/Tuple.h"

#include "dispersion/StandardDeviation.h"
#include "dispersion/VariationCoefficient.h"
#include "dispersion/JuillandD.h"
#include "dispersion/DistributionalConsistency.h"
#include "dispersion/LynesD3.h"
#include "dispersion/TermFrequencyInverseDocumentFrequency.h"

#include "association/Frequency.h"
#include "association/ExpectedFrequency.h"
#include "association/InversedExpectedFrequency.h"
#include "association/Jaccard.h"
#include "association/Dice.h"
#include "association/Sorgenfrei.h"
#include "association/OddsRatio.h"
#include "association/UnigramSubtuples.h"
#include "association/Cvalue.h"
#include "association/ConsonniT1.h"
#include "association/ConsonniT2.h"
#include "association/MutualExpectation.h"
#include "association/SpecificInformation.h"
#include "association/SpecificCorrelation.h"
#include "association/WSpecificCorrelation.h"
#include "association/SpecificMutualDependency.h"
#include "association/SpecificFrequencyBiasedMutualDependency.h"
#include "association/SpecificExponentialCorrelation.h"
#include "association/WSpecificExponentialCorrelation.h"
#include "association/TScore.h"
#include "association/ZScore.h"
#include "association/PearsonsChiSquare.h"
#include "association/WChiSquare.h"
#include "association/LogLikelihood.h"
#include "association/FairDispersionPointNormalization.h"
#include "association/AverageBigram.h"
#include "association/SmoothedBigram.h"
#include "association/MinimalBigram.h"
#include "association/WOrder.h"
#include "association/WTFOrder.h"

#include "association/VectorAssociationMeasure.h"

#include "../machine_learning/multilayer_perceptron/MultilayerPerceptron.h"

#include "quality/Hit.h"
#include "quality/PrecisionCurve.h"
#include "quality/AveragePrecision.h"
#include "quality/AveragePrecisionRecallCurve.h"
#include "quality/MeanAveragePrecision.h"
#include "quality/AveragePrecisionOnHit.h"
#include "quality/RecallCurve.h"
#include "quality/PrecisionRecallCurve.h"
#include "quality/FMeasure.h"
#include "quality/ConfusionMatrixCreator.h"

#include "score/Normalization.h"
#include "score/BordaScore.h"
#include "score/ZipfsBordaScore.h"
#include "score/Centering.h"
#include "score/Standarization.h"
#include "score/ScoreFunctionChain.h"

#include "aggregation/MaxSum.h"
#include "aggregation/MaxMultiplier.h"

#include "../machine_learning/heuristic_optimization/LinearCombination.h"

#include "Creators.h"


namespace function
{


/*******************************************************************/
Creators::FunctionMapping const FilterFunctionCreators::MAPPING({
	{"not",					&Not},

	{"or",					&Or},

	{"and",					&And},

	{"xor",					&Xor},

	{"relation",			&Relation},

	{"frequency",			&Frequency},

	{"corpora_frequency",	&CorporaFrequency},
	{"cf",					&CorporaFrequency},

	{"every_word",			&EveryWord},
	{"ew",					&EveryWord},

	{"tuple",				&Tuple}
});

Creators::FunctionMapping const DispersionFunctionCreators::MAPPING({
	{"standard_deviation",							&StandardDeviation},
	{"sd",											&StandardDeviation},

	{"variance_coefficient",						&VariationCoefficient},
	{"vc",											&VariationCoefficient},

	{"juilland_d",									&JuillandD},
	{"jd",											&JuillandD},

	{"distributional_consistency",					&DistributionalConsistency},
	{"dc",											&DistributionalConsistency},

	{"lynes_d3",									&LynesD3},
	{"ld3",											&LynesD3},

	{"term_frequency_inverse_document_frequency",	&TermFrequencyInverseDocumentFrequency},
	{"tfidf",										&TermFrequencyInverseDocumentFrequency}
});

Creators::FunctionMapping const AssociationFunctionCreators::MAPPING(
{
	{"frequency", 									&Frequency},

	{"expected_frequency",							&ExpectedFrequency},
	{"ef",											&ExpectedFrequency},

	{"inversed_expected_frequency",					&InversedExpectedFrequency},
	{"ief",											&InversedExpectedFrequency},

	{"jaccard",										&Jaccard},

	{"dice",										&Dice},

	{"sorgenfrei",									&Sorgenfrei},

	{"odds_ratio",									&OddsRatio},
	{"or",											&OddsRatio},

	{"unigram_subtuples",							&UnigramSubtuples},
	{"us",											&UnigramSubtuples},

	{"c_value",										&Cvalue},
	{"cval",										&Cvalue},

	{"consonni_t1",									&ConsonniT1},
	{"ct1",											&ConsonniT1},

	{"consonni_t2",									&ConsonniT2},
	{"ct2",											&ConsonniT2},

	{"mutual_expectation",							&MutualExpectation},
	{"me",											&MutualExpectation},

	{"specific_information", 						&SpecificInformation},
	{"si", 											&SpecificInformation},

	{"specific_correlation", 						&SpecificCorrelation},
	{"sc", 											&SpecificCorrelation},

	{"w_specific_correlation", 						&WSpecificCorrelation},
	{"wsc", 										&WSpecificCorrelation},

	{"specific_mutual_dependency", 					&SpecificMutualDependency},
	{"specific_md", 								&SpecificMutualDependency},
	{"smd", 										&SpecificMutualDependency},

	{"specific_frequency_biased_mutual_dependency",	&SpecificFrequencyBiasedMutualDependency},
	{"specific_fbmd", 								&SpecificFrequencyBiasedMutualDependency},
	{"sfbmd", 										&SpecificFrequencyBiasedMutualDependency},

	{"specific_exponential_correlation",			&SpecificExponentialCorrelation},
	{"sec",											&SpecificExponentialCorrelation},

	{"w_specific_exponential_correlation",			&WSpecificExponentialCorrelation},
	{"wsec",										&WSpecificExponentialCorrelation},

	{"tscore",										&TScore},

	{"zscore",										&ZScore},

	{"pearsons_chi_square",							&PearsonsChiSquare},
	{"pearsons_x2",									&PearsonsChiSquare},
	{"px2",											&PearsonsChiSquare},

	{"w_chi_square",								&WChiSquare},
	{"wx2",											&WChiSquare},

	{"loglikelihood",								&LogLikelihood},
	{"g2",											&LogLikelihood},

	{"fair_dispersion_point_normalization",			&FairDispersionPointNormalization},
	{"fdpn",										&FairDispersionPointNormalization},

	{"average_bigram",								&AverageBigram},
	{"abg",											&AverageBigram},

	{"smoothed_bigram",								&SmoothedBigram},
	{"sbg",											&SmoothedBigram},

	{"minimal_bigram",								&MinimalBigram},
	{"mbg",											&MinimalBigram},

	{"w_order",										&WOrder},
	{"wo",											&WOrder},

	{"w_tf_order",									&WTFOrder},
	{"wtfo",										&WTFOrder}
});


Creators::FunctionMapping const VectorAssociationMeasureCreators::MAPPING(
{
	{"vector_association_measure",	&VectorAssociationMeasure},
	{"vam",							&VectorAssociationMeasure}
});


Creators::FunctionMapping const ClassifierCreators::MAPPING(
{
	{"multilayer_perceptron",	&MultilayerPerceptron},
	{"mlp",						&MultilayerPerceptron},
	{"mp",						&MultilayerPerceptron}
});


Creators::FunctionMapping const ScoreFunctionCreators::MAPPING(
{
	{"normalization",			&Normalization},

	{"borda_score", 			&BordaScore},
	{"bs", 						&BordaScore},

	{"zipfs_borda_score", 		&ZipfsBordaScore},
	{"zbs", 					&ZipfsBordaScore},

	{"centering",				&Centering},

	{"standarization",			&Standarization},

	{"score_function_chain",	&ScoreFunctionChain},
	{"sfc",						&ScoreFunctionChain}
});

Creators::FunctionMapping const AggregationFunctionCreators::MAPPING(
{
	{"max_sum", 		&MaxSum},
	{"ms", 				&MaxSum},

	{"max_multiplier", 	&MaxMultiplier},
	{"mm", 				&MaxMultiplier}
});

Creators::FunctionMapping const QualityFunctionCreators::MAPPING(
{
	{"hit", 							&Hit},

	{"precision_curve", 				&PrecisionCurve},
	{"pc", 								&PrecisionCurve},

	{"average_precision", 				&AveragePrecision},
	{"ap", 								&AveragePrecision},

	{"average_precision_recall_curve", 	&AveragePrecisionRecallCurve},
	{"aprc", 							&AveragePrecisionRecallCurve},

	{"mean_average_precision",			&MeanAveragePrecision},
	{"map",								&MeanAveragePrecision},

	{"average_precision_on_hit", 		&AveragePrecisionOnHit},
	{"apoh", 							&AveragePrecisionOnHit},

	{"recall_curve", 					&RecallCurve},
	{"rc", 								&RecallCurve},

	{"precision_recall_curve", 			&PrecisionRecallCurve},
	{"prc", 							&PrecisionRecallCurve},

	{"f_measure",						&FMeasure},
	{"fm",								&FMeasure},

	{"confusion_matrix_creator",		&ConfusionMatrixCreator},
	{"cmc",								&ConfusionMatrixCreator}
});

Creators::FunctionMapping const OptimizationFunctionCreators::MAPPING(
{
	{"linear_combination", 				&LinearCombination},
	{"lc", 								&LinearCombination}
});
/*******************************************************************/


/* Static functions - creators */
/* Filters */
auto FilterFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto FilterFunctionCreators::Not() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Not());
}


auto FilterFunctionCreators::Or() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Or());
}


auto FilterFunctionCreators::And() -> FunctionPtrS
{
	return FunctionPtrS(new filter::And());
}


auto FilterFunctionCreators::Xor() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Xor());
}


auto FilterFunctionCreators::Relation() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Relation());
}


auto FilterFunctionCreators::Frequency() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Frequency());
}


auto FilterFunctionCreators::CorporaFrequency() -> FunctionPtrS
{
	return FunctionPtrS(new filter::CorporaFrequency());
}


auto FilterFunctionCreators::EveryWord() -> FunctionPtrS
{
	return FunctionPtrS(new filter::EveryWord());
}


auto FilterFunctionCreators::Tuple() -> FunctionPtrS
{
	return FunctionPtrS(new filter::Tuple());
}
/* !Filters */


/* Dispersions */
auto DispersionFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto DispersionFunctionCreators::StandardDeviation() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::StandardDeviation());
}


auto DispersionFunctionCreators::VariationCoefficient() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::VariationCoefficient());
}


auto DispersionFunctionCreators::JuillandD() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::JuillandD());
}


auto DispersionFunctionCreators::DistributionalConsistency() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::DistributionalConsistency());
}


auto DispersionFunctionCreators::LynesD3() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::LynesD3());
}


auto DispersionFunctionCreators::TermFrequencyInverseDocumentFrequency() -> FunctionPtrS
{
	return FunctionPtrS(new dispersion::TermFrequencyInverseDocumentFrequency());
}
/* !Dispersions */


/* Associations */
auto AssociationFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto AssociationFunctionCreators::Frequency() -> FunctionPtrS
{
	return FunctionPtrS(new association::Frequency());
}


auto AssociationFunctionCreators::ExpectedFrequency() -> FunctionPtrS
{
	return FunctionPtrS(new association::ExpectedFrequency());
}


auto AssociationFunctionCreators::InversedExpectedFrequency() -> FunctionPtrS
{
	return FunctionPtrS(new association::InversedExpectedFrequency());
}


auto AssociationFunctionCreators::Jaccard() -> FunctionPtrS
{
	return FunctionPtrS(new association::Jaccard());
}


auto AssociationFunctionCreators::Dice() -> FunctionPtrS
{
	return FunctionPtrS(new association::Dice());
}


auto AssociationFunctionCreators::Sorgenfrei() -> FunctionPtrS
{
	return FunctionPtrS(new association::Sorgenfrei());
}


auto AssociationFunctionCreators::OddsRatio() -> FunctionPtrS
{
	return FunctionPtrS(new association::OddsRatio());
}


auto AssociationFunctionCreators::UnigramSubtuples() -> FunctionPtrS
{
	return FunctionPtrS(new association::UnigramSubtuples());
}


auto AssociationFunctionCreators::Cvalue() -> FunctionPtrS
{
	return FunctionPtrS(new association::Cvalue());
}


auto AssociationFunctionCreators::ConsonniT1() -> FunctionPtrS
{
	return FunctionPtrS(new association::ConsonniT1());
}


auto AssociationFunctionCreators::ConsonniT2() -> FunctionPtrS
{
	return FunctionPtrS(new association::ConsonniT2());
}


auto AssociationFunctionCreators::MutualExpectation() -> FunctionPtrS
{
	return FunctionPtrS(new association::MutualExpectation());
}


auto AssociationFunctionCreators::SpecificInformation() -> FunctionPtrS
{
	return FunctionPtrS(new association::SpecificInformation());
}


auto AssociationFunctionCreators::SpecificCorrelation() -> FunctionPtrS
{
	return FunctionPtrS(new association::SpecificCorrelation());
}


auto AssociationFunctionCreators::WSpecificCorrelation() -> FunctionPtrS
{
	return FunctionPtrS(new association::WSpecificCorrelation());
}


auto AssociationFunctionCreators::SpecificMutualDependency() -> FunctionPtrS
{
	return FunctionPtrS(new association::SpecificMutualDependency());
}


auto AssociationFunctionCreators::SpecificFrequencyBiasedMutualDependency() -> FunctionPtrS
{
	return FunctionPtrS(new association::SpecificFrequencyBiasedMutualDependency());
}


auto AssociationFunctionCreators::SpecificExponentialCorrelation() -> FunctionPtrS
{
	return FunctionPtrS(new association::SpecificExponentialCorrelation());
}


auto AssociationFunctionCreators::WSpecificExponentialCorrelation() -> FunctionPtrS
{
	return FunctionPtrS(new association::WSpecificExponentialCorrelation());
}


auto AssociationFunctionCreators::TScore() -> FunctionPtrS
{
	return FunctionPtrS(new association::TScore());
}


auto AssociationFunctionCreators::ZScore() -> FunctionPtrS
{
	return FunctionPtrS(new association::ZScore());
}


auto AssociationFunctionCreators::PearsonsChiSquare() -> FunctionPtrS
{
	return FunctionPtrS(new association::PearsonsChiSquare());
}


auto AssociationFunctionCreators::WChiSquare() -> FunctionPtrS
{
	return FunctionPtrS(new association::WChiSquare());
}


auto AssociationFunctionCreators::LogLikelihood() -> FunctionPtrS
{
	return FunctionPtrS(new association::LogLikelihood());
}


auto AssociationFunctionCreators::FairDispersionPointNormalization() -> FunctionPtrS
{
	return FunctionPtrS(new association::FairDispersionPointNormalization());
}


auto AssociationFunctionCreators::AverageBigram() -> FunctionPtrS
{
	return FunctionPtrS(new association::AverageBigram());
}


auto AssociationFunctionCreators::SmoothedBigram() -> FunctionPtrS
{
	return FunctionPtrS(new association::SmoothedBigram());
}


auto AssociationFunctionCreators::MinimalBigram() -> FunctionPtrS
{
	return FunctionPtrS(new association::MinimalBigram());
}


auto AssociationFunctionCreators::WOrder() -> FunctionPtrS
{
	return FunctionPtrS(new association::WOrder());
}


auto AssociationFunctionCreators::WTFOrder() -> FunctionPtrS
{
	return FunctionPtrS(new association::WTFOrder());
}
/* !Associations */


/* !Association vector */
auto VectorAssociationMeasureCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto VectorAssociationMeasureCreators::VectorAssociationMeasure() -> FunctionPtrS
{
	return FunctionPtrS(new association::VectorAssociationMeasure());
}
/* !Association vector */


/* !Classifier */
auto ClassifierCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto ClassifierCreators::MultilayerPerceptron() -> FunctionPtrS
{
	return FunctionPtrS(new machine_learning::multilayer_perceptron::MultilayerPerceptron());
}
/* !Classifier */


/* Scores */
auto ScoreFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto ScoreFunctionCreators::Normalization() -> FunctionPtrS
{
	return FunctionPtrS(new score::Normalization());
}


auto ScoreFunctionCreators::BordaScore() -> FunctionPtrS
{
	return FunctionPtrS(new score::BordaScore());
}


auto ScoreFunctionCreators::ZipfsBordaScore() -> FunctionPtrS
{
	return FunctionPtrS(new score::ZipfsBordaScore());
}


auto ScoreFunctionCreators::Centering() -> FunctionPtrS
{
	return FunctionPtrS(new score::Centering());
}


auto ScoreFunctionCreators::Standarization() -> FunctionPtrS
{
	return FunctionPtrS(new score::Standarization());
}


auto ScoreFunctionCreators::ScoreFunctionChain() -> FunctionPtrS
{
	return FunctionPtrS(new score::ScoreFunctionChain());
}
/* !Scores */


/* Aggregators */
auto AggregationFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto AggregationFunctionCreators::MaxSum() -> FunctionPtrS
{
	return FunctionPtrS(new aggregation::MaxSum());
}


auto AggregationFunctionCreators::MaxMultiplier() -> FunctionPtrS
{
	return FunctionPtrS(new aggregation::MaxMultiplier());
}
/* !Aggregators */


/* Qualities */
auto QualityFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto QualityFunctionCreators::Hit() -> FunctionPtrS
{
	return FunctionPtrS(new quality::Hit());
}


auto QualityFunctionCreators::PrecisionCurve() -> FunctionPtrS
{
	return FunctionPtrS(new quality::PrecisionCurve());
}


auto QualityFunctionCreators::AveragePrecision() -> FunctionPtrS
{
	return FunctionPtrS(new quality::AveragePrecision());
}


auto QualityFunctionCreators::AveragePrecisionRecallCurve() -> FunctionPtrS
{
	return FunctionPtrS(new quality::AveragePrecisionRecallCurve());
}


auto QualityFunctionCreators::MeanAveragePrecision() -> FunctionPtrS
{
	return FunctionPtrS(new quality::MeanAveragePrecision());
}


auto QualityFunctionCreators::AveragePrecisionOnHit() -> FunctionPtrS
{
	return FunctionPtrS(new quality::AveragePrecisionOnHit());
}


auto QualityFunctionCreators::RecallCurve() -> FunctionPtrS
{
	return FunctionPtrS(new quality::RecallCurve());
}


auto QualityFunctionCreators::PrecisionRecallCurve() -> FunctionPtrS
{
	return FunctionPtrS(new quality::PrecisionRecallCurve());
}


auto QualityFunctionCreators::FMeasure() -> FunctionPtrS
{
	return FunctionPtrS(new quality::FMeasure());
}


auto QualityFunctionCreators::ConfusionMatrixCreator() -> FunctionPtrS
{
	return FunctionPtrS(new quality::ConfusionMatrixCreator());
}
/* !Qualities */


/* Optimization functions */
auto OptimizationFunctionCreators::getMapping() -> FunctionMapping const&
{
	return MAPPING;
}


auto OptimizationFunctionCreators::LinearCombination() -> FunctionPtrS
{
	return FunctionPtrS(new machine_learning::heuristic_optimization::LinearCombination());
}
/* !Optimization functions */


}
