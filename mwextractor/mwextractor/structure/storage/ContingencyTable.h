
#pragma once

#include <cstddef>
#include <vector>
#include <string>


namespace structure
{
	namespace storage
	{


/**
 * \brief Tablica przechowująca informacje o współwystępowaniu
 * elementów.
 *
 * Tablica przechowuje informacje o współwystępowaniu
 * określonej liczby elementów.
 * Informacja w niej jest zakodowano bitowo w celu zmnijeszenia
 * wykorzystania pamięci.
 *
 * Opis zawartości:
 * Każde pole tablicy przechowuje informacje o jednej kombinacji
 * elementów - wartość zaobserwowaną i oczekiwaną dla tej
 * kombinacji elementów.
 * Za kombinacje uznaje się wszystkie kombinacje mające zachowaną
 * kolejność elementów, ale mogącą nie zawierać ich wszystkich.
 * Przykładowo dla dwóch elementów AB tablica będzie miała
 * 2^liczba_elementów * 2 wartości, ponieważ dla tej pary
 * elementów istnieją 4 kombinacje AB Ax xB xx, a dla każdej
 * z nich dwie wartości - zaobserwowana i oczekiwana.
 *
 * Kodowanie:
 *
 * Przykład:
 *	Rozważmy 3-elementową krotkę ABC, tablica złożona jest
 *	z 8 pól po dwie wartości.
 *	Każdy indeks w tablicy jest kodem określającym jakie wzorzec
 *	przedstawia dane pole - jakie elementy są takie same jak w
 *	ciągu na odpowiadającej pozycji, a które są inne niż te
 *	znajdujące się na odpowiedniej pozycji w tym ciągu.
 *	Każdy indeks to maska bitowa, gdzie 0 na danej pozycji
 *	informuje, że element jest taki sam jak w ciągu, a 1
 *	że element jest inny niż ten w ciągu na danej pozycji.
 *	Przykładowo maska b110 (6) czytana od prawej do lewej
 *	oznacza, że element na pozycji pierwszej jest taki sam
 *	jak w ciągu, a dwa kolejne są inne niż w ciągu, czyli
 *	A ~B ~C (A, nie B, nie C).
 *	Innymi słowy pod indeksem 6 znajdują się informacje o
 *	wartości zaobserwowanej i oczekiwanej o ciągach A ~B ~C.
 *
 *~~~
 *	Przykłady kodowania:
 *	------------------------
 *	~ oznacza negację
 *	-------------------------
 *	index tablicy = forma binarna = kodowana krotka
 *	-------------------------  	--			   --
 *	0 = b000 =  A  B  C   		|			   |
 *	1 = b001 = ~A  B  C   		| 2 elementowa |
 *	2 = b010 =  A ~B  C   		| krotka (AB)  |
 *	3 = b011 = ~A ~B  C   		|			   |
 *	-------------------------  	--			   | 3 elementowa
 *	4 = b100 =  A  B ~C				  		   | krotka (ABC)
 *	5 = b101 = ~A  B ~C				   		   | ...
 *	6 = b110 =  A ~B ~C				   		   | i tak dalej...
 *	7 = b111 = ~A ~B ~C				   		   |
 *	-------------------------				   --
 *
 *	Obserwacja:
 *	~A B C D; A ~B C D; A B ~C D; A B C ~D; -> indeksy: 1, 2, 4, 8
 *~~~
 */
class ContingencyTable
{
public:
	struct ContingencyValue
	{
		ContingencyValue(
			double pObserved = 0.0,
			double pExpected = 0.0);

		double observed;
		double expected;
	};


public:
	ContingencyTable(size_t pSpace);
	ContingencyTable(
		size_t 					pSpace,
		ContingencyValue const& pValue);

	ContingencyTable() 											= default;
	ContingencyTable(ContingencyTable&& 				pTable)	= default;
	ContingencyTable(ContingencyTable const& 			pTable)	= default;
	ContingencyTable& operator=(ContingencyTable&& 		pTable)	= default;
	ContingencyTable& operator=(ContingencyTable const& pTable) = default;

	~ContingencyTable() = default;


	ContingencyValue const& operator[](size_t pIndex) const;
	ContingencyValue& 		operator[](size_t pIndex);

	ContingencyValue const* data() const;
	ContingencyValue* 		data();

	size_t size() 		const;
	size_t tupleSize()	const;

	ContingencyTable gatherObservedBigramData(size_t pBigramIndex) const;

	/**
	 * \brief Funkcja wyciąga wartości dla zadanego N-gramu.
	 *
	 * Funkcja wyciąga wartości dla N-gramu o indeksie
	 * pNgramIndex i długości pNgramLength.
	 * Funkcja do wykonania tego zadania sumuje odpowiednie pola
	 * tablicy.
	 *
	 * Przykład:
	 * Dla krotki ABCDE i parametrów pBigramIndex = 1 i
	 * pNgramLength = 2 funkcja wyciągnie informacje z tablicy
	 * dla ngramu BC.
	 *
	 * @param pNgramIndex indeks N-gramu, dla którego wartości
	 * mają zostać wyliczone, poprawne wartości są z zakresu
	 * od 0 do N-1.
	 * @param pNgramLength długość N-gramu, dla którego wartości
	 * mają zostać wyliczone, poprawne wartości są z zakresu
	 * od 1 do N-1 - pBigramIndex.
	 *
	 */
	ContingencyTable gatherObservedNgramData(
		size_t pNgramIndex,
		size_t pNgramLength) const;

	/**
	 * \brief Funkcja kompresuje N-elementowej krotki w
	 * 2-elementową.
	 *
	 * Funkcja kompresuje dane zaobserwowane z N-elementowej
	 * krotki do 2-elementowej krotki.
	 * Punkt dyspersji (pDispersionPoint) określa, w którym
	 * punkcie należy rozdzielić krotkę.
	 * Wszystkie elementy po lewej stronie będą traktowane
	 * jako pojedynczy element lewy, a po prawej jako jeden
	 * prawy element.
	 *
	 * Przykładowo:
	 * Dla krotki ABCD z pDispersionPoint o wartości 1 zostanie
	 * utworzona krotka XY, gdzie X = A, a Y - BCD.
	 */
	ContingencyTable compressObservedToBigram(size_t pDispersionPoint) const;

	/**
	 * \brief Funkcja oblicza wartrości oczekiwane
	 *
	 * Przetestowana. Funkcja oblicza wartości oczekiwane
	 * dla danych zaobserwowanych.
	 */
	void computeExpected(size_t pObservedSum);
	void computeExpected();

	double sumObserved() const;
	double sumExpected() const;

	std::string createReprezentation() const;

private:
	std::vector<ContingencyValue> mValues;
};


	}
}
