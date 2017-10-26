/*
 * AbstractOrderAssociationFunction.h
 *
 *  Created on: 23 maj 2014
 *      Author: michalw
 */

#pragma once

#include <map>
#include <vector>
#include <memory>

#include "../../structure/storage/RelationStorage.h"
#include "AssociationFunction.h"


namespace function
{
	namespace association
	{


/**
 *	\brief Klasa bazowa dla funkcji opierających się o badanie szyku krotek.
 *
 *	Funkcje te bazują na schematach relacji.
 *	Każdy z nich zawiera w sobie informacje o pewnych grupach relacji.
 *	Pojedyncza linia w pliku zawiera nazwy N relacji oddzielone tabulacjami.
 *	Taka linia jest definicją grupy relacji, w obrębie których występować
 *	mogą występować dane krotki. Przykładowo relacja SubstAdj, SubstAdj1H oraz
 *	SubstAdj2H powinny występować w obrębie jednej grupy relacji jeśli
 *	pierwsza wyszukuje połączenia ciągłe subst i adj, druga nieciągłe z
 *	pojedynczą dziruą, a trzecia analogicznie nieciągłe z podwóją dziurą.
 *	Przykładowy plik schematu:
 *	~~~
 *	SubstAdj<\t>SubstAdj1H<\t>SubstAdj2H<\t>AdjSubst<\t>AdjSubst1H<\t>AdjSubst2H
 *	SubstSubst<\t>SubstSubst1H<\t>SubstSubst2H
 *	~~~
 *	Pierwsza linia to ogólna grupa relacji dla połączeń subst i adj,
 *	a linia druga to ogólna grupa relacji dla połączeń subst i subst.
 *	Jeśli przykładowo sprawdzana będzie siła połączenia wyrażenia
 *	czerowna kartka (AdjSubst) to wykorzystany powinien zostać schemat grupy
 *	zapisany w pierwszej linii pliku, a tym samym informacje o 6 różnych
 *	relacjach. To w obrębie tych relacji wyszukiwana będzie dana krotka
 *	i sprawdzane będą częstości jej wystąpienia w różnych typach strukturalnych.
 */
class AbstractOrderAssociationFunction : public AssociationFunction
{
public:
	typedef std::shared_ptr<AssociationFunction> 				AssociationFunctionPtrS;

	typedef structure::storage::RelationStorage::RelationScheme	RelationScheme;


public:
	AbstractOrderAssociationFunction()																						= default;
	AbstractOrderAssociationFunction(AbstractOrderAssociationFunction&& 				pAbstractOrderAssociationFunction)	= default;
	AbstractOrderAssociationFunction(AbstractOrderAssociationFunction const& 			pAbstractOrderAssociationFunction)	= default;
	AbstractOrderAssociationFunction& operator=(AbstractOrderAssociationFunction&& 		pAbstractOrderAssociationFunction)	= default;
	AbstractOrderAssociationFunction& operator=(AbstractOrderAssociationFunction const& pAbstractOrderAssociationFunction)	= default;

	virtual ~AbstractOrderAssociationFunction() = default;

	virtual void initialize(RankerDataPtrS const& pRankerDataPtrS);


	RelationScheme const& 	getRelationScheme() const;
	RelationScheme& 		getRelationScheme();


	virtual double rankUsingTable(
		TupleId 				pTupleId,
		ContingencyTable const& pContingencyTable) const override;


private:
	RelationScheme mRelationScheme;
};


	}
}
