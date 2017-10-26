/*
 * SingleIterator.h
 *
 *  Created on: 8 sie 2014
 *      Author: michalw
 */

#pragma once


namespace structure
{
	namespace container
	{


template <typename Key, typename Value>
struct FirstValueGetter
{
	typedef std::pair<Key, Value> __Argument;

	Key const& get(__Argument const& pArgument) const;
};

template <typename Key, typename Value>
Key const& FirstValueGetter<Key, Value>::get(__Argument const& pArgument) const
{
	return pArgument.first;
}



template <typename Key, typename Value>
struct SecondValueGetter
{
	typedef std::pair<Key, Value> __Argument;

	Value const& get(__Argument const& pArgument) const;
};

template <typename Key, typename Value>
Value const& SecondValueGetter<Key, Value>::get(__Argument const& pArgument) const
{
	return pArgument.second;
}



template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
class SingleIterator {
public:
	SingleIterator(KeyValueIterator pIterator);

	SingleIterator(SingleIterator&& 				pIterator) = default;
	SingleIterator(SingleIterator const& 			pIterator) = default;
	SingleIterator& operator=(SingleIterator&& 		pIterator) = default;
	SingleIterator& operator=(SingleIterator const& pIterator) = default;

	~SingleIterator() = default;


	SingleIterator&		operator++();
	SingleIterator		operator++(int) const;

	bool				operator!=(SingleIterator const& pIterator) const;

	ReturnType			operator*() const;


private:
	KeyValueIterator 	mIterator;
	ValueGetter			mGetter;
};


template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
SingleIterator<KeyValueIterator, ReturnType, ValueGetter>::SingleIterator(KeyValueIterator pIterator)
:
	mIterator(pIterator)
{

}


template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
auto SingleIterator<KeyValueIterator, ReturnType, ValueGetter>::operator++() -> SingleIterator&
{
	++mIterator;
	return (*this);
}


template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
auto SingleIterator<KeyValueIterator, ReturnType, ValueGetter>::operator++(int) const -> SingleIterator
{
	SingleIterator i = (*this);
	++mIterator;
	return i;
}


template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
bool SingleIterator<KeyValueIterator, ReturnType, ValueGetter>::operator!=(SingleIterator const& pIterator) const
{
	return mIterator != pIterator.mIterator;
}


template <typename KeyValueIterator, typename ReturnType, typename ValueGetter>
ReturnType SingleIterator<KeyValueIterator, ReturnType, ValueGetter>::operator*() const
{
	return mGetter.get(*mIterator);
}


	}
}
