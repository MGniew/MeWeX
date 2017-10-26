#pragma once

/**
 * \file Time.h
 * \brief Metoda służąca do mierzenia czasu.
 */


#include <sys/time.h>


namespace utils
{


/**
 * \brief Klasa opakowująca funkcjonalność związaną z mierzeniem
 * czasu.
 *
 * Utworzenie obiektu zapisuje czas, w którym został on utworzony.
 * Przykład użycia:
 * ~~~
 * Time a;
 * jakiesZadanie();
 * Time b;
 * std::cout << (b - a) << std::endl;
 * ~~~
 */
class Time
{
private:
	typedef timespec TimeValue;

public:
	Time();

	Time(Time&& 				pTime) = default;
	Time(Time const& 			pTime) = default;
	Time& operator=(Time const& pTime) = default;

	~Time() = default;


	double inSeconds() const;

	double difference(Time const& pTime) 	const;
	double operator-(Time const& pTime) 	const;


private:
	void update();


private:
	TimeValue mTime;
};


}
