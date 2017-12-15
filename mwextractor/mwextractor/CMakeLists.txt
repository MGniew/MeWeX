cmake_minimum_required(VERSION 2.6)
project(MWeXtractor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)


###########################################################
# libs stuff:
find_package(Corpus2 1.0.9 REQUIRED)
set(LIBS ${LIBS} ${Corpus2_LIBRARIES} rt)

find_package(PwrUtils 1.0.1 REQUIRED)
set(LIBS ${LIBS} ${PwrUtils_LIBRARY})

find_package(Boost COMPONENTS program_options system)
link_directories(${Boost_LIBRARY_DIRS})
set(LIBS ${LIBS} ${Boost_LIBRARIES})

find_package(ICU REQUIRED)
include_directories(${ICU_INCLUDE_DIR})
set(LIBS ${LIBS} ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES})

find_package(ANTLR REQUIRED)
include_directories(${ANTLR_INCLUDE_DIR})

set(LIBS ${LIBS} corpus2 wccl antlr)


###########################################################
# library build:
set(SOURCE_DIRS_PREFIX ${CMAKE_CURRENT_LIST_DIR})

# utilities
set(UTILS_SRCS
	${SOURCE_DIRS_PREFIX}/utils/Debug.cpp
	${SOURCE_DIRS_PREFIX}/utils/File.cpp
	${SOURCE_DIRS_PREFIX}/utils/Textual.cpp
	${SOURCE_DIRS_PREFIX}/utils/Random.cpp
	${SOURCE_DIRS_PREFIX}/utils/Time.cpp
	${SOURCE_DIRS_PREFIX}/utils/Parallel.cpp)

set(EXCEPTION_SRCS
	${SOURCE_DIRS_PREFIX}/exception/Exception.cpp)

# storage sources
set(STORAGE_SRCS
	${SOURCE_DIRS_PREFIX}/structure/storage/Corpora.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/RawFrequencyStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/CompressedFrequencyStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/CorporaStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/PartOfSpeechStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/WordStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/RelationStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/MatrixTupleStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/RelevantTuple.cpp)

# statistic data sources
set(STATISTICS_DATA_SRCS
	${SOURCE_DIRS_PREFIX}/structure/storage/ContingencyTable.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/ContingencyTableGenerator.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/ContingencyTableStorage.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/Instance.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/TupleFeatureGenerator.cpp
	${SOURCE_DIRS_PREFIX}/structure/storage/TupleFeatureStorage.cpp)
	
# functions srcs
set(FUNCTIONS_SRCS	
	${SOURCE_DIRS_PREFIX}/function/Function.cpp
	${SOURCE_DIRS_PREFIX}/function/FunctionFactory.cpp
	${SOURCE_DIRS_PREFIX}/function/Creators.cpp
	
	${SOURCE_DIRS_PREFIX}/function/dispersion/DispersionData.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/Disperser.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/DispersionFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/StandardDeviation.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/VariationCoefficient.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/JuillandD.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/DistributionalConsistency.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/LynesD3.cpp
	${SOURCE_DIRS_PREFIX}/function/dispersion/TermFrequencyInverseDocumentFrequency.cpp
	
	${SOURCE_DIRS_PREFIX}/function/filter/Filtrator.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Filter.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/FeatureFilter.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/FilterChain.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Not.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Or.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/And.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Xor.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Frequency.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/CorporaFrequency.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Relation.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/EveryWord.cpp
	${SOURCE_DIRS_PREFIX}/function/filter/Tuple.cpp
	
	${SOURCE_DIRS_PREFIX}/function/association/RankerData.cpp
	${SOURCE_DIRS_PREFIX}/function/association/Extractor.cpp
	${SOURCE_DIRS_PREFIX}/function/association/CrossValidator.cpp
	${SOURCE_DIRS_PREFIX}/function/association/AbstractRanker.cpp
	${SOURCE_DIRS_PREFIX}/function/association/AssociationMeasure.cpp 
	${SOURCE_DIRS_PREFIX}/function/association/VectorAssociationMeasure.cpp
	${SOURCE_DIRS_PREFIX}/function/association/AssociationFunction.cpp 
	${SOURCE_DIRS_PREFIX}/function/association/AssociationFunctionBased.cpp
	${SOURCE_DIRS_PREFIX}/function/association/AbstractOrderAssociationFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/association/Frequency.cpp
	${SOURCE_DIRS_PREFIX}/function/association/ExpectedFrequency.cpp
	${SOURCE_DIRS_PREFIX}/function/association/InversedExpectedFrequency.cpp
	${SOURCE_DIRS_PREFIX}/function/association/Jaccard.cpp
	${SOURCE_DIRS_PREFIX}/function/association/Dice.cpp
	${SOURCE_DIRS_PREFIX}/function/association/Sorgenfrei.cpp
	${SOURCE_DIRS_PREFIX}/function/association/OddsRatio.cpp
	${SOURCE_DIRS_PREFIX}/function/association/UnigramSubtuples.cpp
	${SOURCE_DIRS_PREFIX}/function/association/ConsonniT1.cpp
	${SOURCE_DIRS_PREFIX}/function/association/ConsonniT2.cpp
	${SOURCE_DIRS_PREFIX}/function/association/MutualExpectation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SpecificInformation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SpecificCorrelation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/WSpecificCorrelation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SpecificMutualDependency.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SpecificFrequencyBiasedMutualDependency.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SpecificExponentialCorrelation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/WSpecificExponentialCorrelation.cpp
	${SOURCE_DIRS_PREFIX}/function/association/TScore.cpp
	${SOURCE_DIRS_PREFIX}/function/association/ZScore.cpp
	${SOURCE_DIRS_PREFIX}/function/association/PearsonsChiSquare.cpp
	${SOURCE_DIRS_PREFIX}/function/association/WChiSquare.cpp
	${SOURCE_DIRS_PREFIX}/function/association/LogLikelihood.cpp
	${SOURCE_DIRS_PREFIX}/function/association/FairDispersionPointNormalization.cpp
	${SOURCE_DIRS_PREFIX}/function/association/AverageBigram.cpp
	${SOURCE_DIRS_PREFIX}/function/association/SmoothedBigram.cpp
	${SOURCE_DIRS_PREFIX}/function/association/MinimalBigram.cpp
	${SOURCE_DIRS_PREFIX}/function/association/WOrder.cpp
	${SOURCE_DIRS_PREFIX}/function/association/WTFOrder.cpp
	
	${SOURCE_DIRS_PREFIX}/function/score/ScoreFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/score/ScoreFunctionChain.cpp
	${SOURCE_DIRS_PREFIX}/function/score/Normalization.cpp
	${SOURCE_DIRS_PREFIX}/function/score/BordaScore.cpp
	${SOURCE_DIRS_PREFIX}/function/score/ZipfsBordaScore.cpp
	${SOURCE_DIRS_PREFIX}/function/score/Centering.cpp
	${SOURCE_DIRS_PREFIX}/function/score/Standarization.cpp
	
	${SOURCE_DIRS_PREFIX}/function/aggregation/AggregationFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/aggregation/MaxSum.cpp
	${SOURCE_DIRS_PREFIX}/function/aggregation/MaxMultiplier.cpp
	
	${SOURCE_DIRS_PREFIX}/function/quality/QualityMatrix.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/QualityFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/Hit.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/PrecisionCurve.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/AveragePrecision.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/AveragePrecisionRecallCurve.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/MeanAveragePrecision.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/AveragePrecisionOnHit.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/RecallBasedQualityFunction.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/RecallCurve.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/PrecisionRecallCurve.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/FMeasure.cpp
	${SOURCE_DIRS_PREFIX}/function/quality/ConfusionMatrixCreator.cpp)

# machine learning
set(LEARNING_SRCS
	${SOURCE_DIRS_PREFIX}/machine_learning/Classifier.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/OptimizationFunction.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/multilayer_perceptron/Neuron.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/multilayer_perceptron/Layer.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/multilayer_perceptron/MultilayerPerceptron.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/multilayer_perceptron/Model.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/BaseCallPoliciesArguments.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/BaseReport.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/RandomSearch/CallPoliciesArgumentsRS.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/HillClimbing/CallPoliciesArgumentsHC.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/TabuSearch/CallPoliciesArgumentsTS.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/SimulatedAnnealing/CallPoliciesArgumentsSA.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/EvolutionaryAlgorithm/CallPoliciesArgumentsEA.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/EvolutionaryAlgorithm/Individual.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/PSO/CallPoliciesArgumentsPSO.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/PSO/Particle.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/Data.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/DoubleEvaluationPerformance.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/DoubleParameter.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/EvaluationPerformanceFactory.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/Evaluator.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/EvaluatorWrapper.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/Exception/Exception.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/HypersphereNeighbourhood.cpp 
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/IntEvaluationPerformance.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/IntParameter.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/LinearCombination.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/ParameterFactory.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/Point.cpp
	${SOURCE_DIRS_PREFIX}/machine_learning/heuristic_optimization/Random.cpp)

# builders
set(BUILDER_SRCS
	${SOURCE_DIRS_PREFIX}/structure/builder/CorporaParser.cpp
	${SOURCE_DIRS_PREFIX}/structure/builder/ContingencyTableGeneratorBuilder.cpp
	${SOURCE_DIRS_PREFIX}/structure/builder/ContingencyTableStorageBuilder.cpp
	${SOURCE_DIRS_PREFIX}/structure/builder/TupleFeatureStorageBuilder.cpp
	${SOURCE_DIRS_PREFIX}/structure/builder/OrthExtractor.cpp)

# io sources
set(IO_SRCS
	${SOURCE_DIRS_PREFIX}/structure/io/StreamingFileReader.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/AbstractTupleStorageIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/DecodedTupleStorageIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/ContingencyTableStorageIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/ContingencyTableGeneratorIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/WordnetRelevantChainWordSetLoader.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/RelevantTupleSetLoader.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/KBestTupleListIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/KBestTupleWithOrthsListIO.cpp
	${SOURCE_DIRS_PREFIX}/structure/io/ArffTupleFeatureStorageIO.cpp)

set(PROGRAM_SRCS
	${SOURCE_DIRS_PREFIX}/program/AbstractConfig.cpp)

set(MWEXTRACTOR_SRCS
	${UTILS_SRCS}
	${EXCEPTION_SRCS}
	${STORAGE_SRCS} 
	${STATISTICS_DATA_SRCS}
	${FUNCTIONS_SRCS}
	${LEARNING_SRCS}
	${BUILDER_SRCS}
	${IO_SRCS}
	${PROGRAM_SRCS})

add_library(mwextractor SHARED ${MWEXTRACTOR_SRCS})
target_link_libraries(mwextractor ${LIBS})
set(LIBS ${LIBS} corpus2 wccl antlr mwextractor)

###########################################################
# output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###########################################################
# programs
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/tuples_builder/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/cover/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/reductor/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/normalizer/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/continger/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/indexer/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/feature_maker/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/miner/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/digger/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/judger/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/teacher/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/web_tool/)
 add_subdirectory(${SOURCE_DIRS_PREFIX}/program/heuristic/)


###########################################################
# install
install(PROGRAMS 
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WebTool 
		DESTINATION bin)

###########################################################
# tester
set(TEST_SRCS
	${SOURCE_DIRS_PREFIX}/main.cpp)
add_executable(Test ${TEST_SRCS})
target_link_libraries(Test ${LIBS})

add_subdirectory(${SOURCE_DIRS_PREFIX}/tests/)