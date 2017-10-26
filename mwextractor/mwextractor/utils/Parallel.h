
#pragma once

/**
 * \file Parallel.h
 * \brief Metody związane z przetwarzaniem równoległym.
 */


#include <vector>
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>


namespace utils
{


size_t maxThreads();


/**
 * \brief Implementacja pętli równoległej z wykorzystaniem
 * biblioteki standardowej.
 *
 * \param _pBegin iteracja nastąpi od tej wartości (włącznie).
 * \param _pEnd iteracja nastąpi do tej wartości (wyłącznie).
 * \param _pCallable obiekt wywoływalny, np. wyrażenie lambda, przyjmujący
 * 		dwa parametery: indeks wątku (typ: size_t) oraz indeks zadania (typ: _pBegin).
 * \param _pThreadCount liczba możliwych do wykorzystania wątków roboczych.
 */
template <typename B, typename E, typename C>
void parallelFor(B _pBegin, E _pEnd, C _pCallable, size_t _pThreadCount = maxThreads())
{
	std::vector<std::thread>	_threads;
	std::mutex					_mutex;
	std::atomic<int>			_idCreator(0);
	for (size_t _innerIter = 0; _innerIter < _pThreadCount; ++_innerIter)
	{
		_threads.emplace_back([&_pBegin,
							   &_pEnd,
							   &_pCallable,
							   &_mutex,
							   &_idCreator]()
		{
			size_t	_threadId = _idCreator.fetch_add(1);
			B		_jobIndex;
			bool 	_done = false;
			while (!_done)
			{
				_mutex.lock();
				if (_pBegin == _pEnd)
				{
					_done = true;
				}
				else
				{
					_jobIndex = _pBegin;
					++_pBegin;
				}
				_mutex.unlock();
				if (!_done)
				{
					_pCallable(_threadId, _jobIndex);
				}
			}
		});
	}

	for (size_t i = 0; i < _pThreadCount; ++i)
	{
		_threads[i].join();
	}
}


}
