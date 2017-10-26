
#pragma once

#include <map>
#include <memory>

#include "../structure/storage/MatrixTupleStorage.h"


namespace function
{


/**
 * \brief Bazowa klasa dla funkcji.
 *
 * Bazowa klasa dla wszystkich funkcji, które mogą być tworzone
 * i zbudowane (preinicjalizacja) z wykorzystaniem fabryki funkcji,
 * są reprezentowalne i mają swoje nazwy.
 *
 * @see FunctionFactory
 */
class Function
{
public:
	typedef std::pair<std::string, std::string>		StringParameter;
	typedef std::multimap<std::string, std::string> StringParameterMap;

	typedef structure::storage::MatrixTupleStorage	TupleStorage;
	typedef TupleStorage const						TupleStorageConst;
	typedef std::shared_ptr<TupleStorageConst>		TupleStorageConstPtrS;

public:
	Function()										= default;
	Function(Function&& 				pFunction)	= default;
	Function(Function const& 			pFunction)	= default;
	Function& operator=(Function&& 		pFunction)	= default;
	Function& operator=(Function const& pFunction)	= default;

	virtual ~Function() = default;


	/**
	 * \brief Metoda ma zwracać dozwolone dla tego typu funkcji
	 * parameterów.
	 *
	 * Metoda zwraca słownik (mapę), który paruje nazwę parametru
	 * (ciąg tekstowy) z pewną wartością (ciąg tekstowy).
	 * Jeśli wartość jest niepusta to parameter nie jest obowiązkowy.
	 * Pusta wartość oznacza, że trzeba go zdefiniować w tekście
	 * zadawanym jako arguemnt dla metody fabryki funkcji, ponieważ
	 * w innym przypadku rzucony zostanie wyjątek.
	 * Wartość parametru "none" oznacza, że parameter nie ma
	 * wartości domyślnej, ale nie trzeba go definiować w ciągu
	 * tekstowym będącym argumentem dla fabryki funkcji.
	 *
	 * @see Exception
	 *
	 */
	virtual StringParameterMap retrieveFunctionParameters() const;

	/**
	 * \brief Budowa funkcji na podstawie argumentów tekstowych.
	 *
	 * Funkcja ma za zadanie zainicjalizowania obiektu na podstawie
	 * ciągów tekstowych.
	 *
	 * \param pParameters parametery nazwane, mapa: nazwa parametru (tekst) -> wartość (tekst).
	 * \param pUnnamedParameters parametery nienazwane, mapa: indeks parameteru (tekst) -> wartość (tekst).
	 */
	virtual void build(
		StringParameterMap const& pParameters,
		StringParameterMap const& pUnnamedParameters);

	/**
	 * \brief Funkcja zwraca nazwę funkcji.
	 */
	virtual std::string	name() const = 0;

	/**
	 * \brief Funkcja zwraca reprezentację funkcji.
	 *
	 * Reprezentacja funkcji to taki ciąg tekstowy, który
	 * może być użyty jako argument dla fabryki funkcji, aby
	 * odtworzyć tę właśnię funkcje (w większości przypadków
	 * łącznie ze stanem).
	 */
	virtual std::string	reprezentation() const;

	/**
	 * \brief Funkcja zwraca przyklad funkcji.
	 *
	 * Funkcja zwraca przykładowy tekst używany do tworzenia tej funkcji.
	 * W przeciwieństwie do funkcji "reprezentation" tekst ten
	 * nie musi być poprawnym argumentem dla fabryki funkcji.
	 *
	 * @see FunctionFactory
	 */
	virtual std::string usage() const;
};


}
