
#pragma once

#include <cstddef>
#include <vector>
#include <ostream>


namespace structure
{
	namespace container
	{


/**
 * \brief Implementacja macierzy dwuwymiarowej.
 */
template <typename T>
class Array2D
{
public:
	typedef typename std::vector<T>::iterator 		Iterator;
	typedef typename std::vector<T>::const_iterator IteratorConst;
	typedef T*										Row;
	typedef T const*								RowConst;

public:
	Array2D(
		size_t 	pRowCount	= 0,
		size_t	pRowSize	= 1,
		T 		pValue 		= 0);

	Array2D(Array2D&& 					pArray2D) = default;
	Array2D(Array2D const& 				pArray2D) = default;
	Array2D& operator=(Array2D&& 		pArray2D) = default;
	Array2D& operator=(Array2D const& 	pArray2D) = default;

	virtual ~Array2D() = default;


	virtual void	writeToStream(
						std::ostream& 	pStream,
						char 			pDelimeter = ' ') const;

	RowConst		getRow(size_t pIndex) const;
	Row				getRow(size_t pIndex);

	T const&		getRowPart(
						size_t pIndex,
						size_t pPart) const;
	T&				getRowPart(
						size_t pIndex,
						size_t pPart);

	RowConst 		operator[](size_t pIndex) const;
	Row				operator[](size_t pIndex);

	Iterator		insert(
						Iterator 	pPosition,
						T const&	pValue);
	Iterator		insert(
						Iterator	pPosition,
						T&& 		pValue);

	Iterator		erase(Iterator pPosition);

	size_t			size()				const;
	size_t			getRowSize() 	const;
	size_t			getRowCount() 	const;

	IteratorConst	begin() const;
	Iterator		begin();
	IteratorConst	end() 	const;
	Iterator		end();

	IteratorConst	beginRow(size_t pRowNumber) const;
	Iterator		beginRow(size_t pRowNumber);
	IteratorConst	endRow(size_t pRowNumber) 	const;
	Iterator		endRow(size_t pRowNumber);

private:
	std::vector<T> 	mData;
	size_t			mRowSize;
};


template <typename T>
Array2D<T>::Array2D(
	size_t 	pRowCount,
	size_t	pRowSize,
	T		pValue)
:
	mData(pRowCount * pRowSize, pValue),
	mRowSize(pRowSize)
{

}


template <typename T>
void Array2D<T>::writeToStream(
	std::ostream& 	pStream,
	char 			pDelimeter) const
{
	for (size_t i = 0; i < mData.size(); ++i)
	{
		pStream << mData[i] << ((i + 1) % mRowSize == 0 ? '\n' : pDelimeter);
	}
}


template <typename T>
auto Array2D<T>::getRow(size_t pIndex) const -> RowConst
{
	return mData.data() + getRowSize() * pIndex;
}


template <typename T>
auto Array2D<T>::getRow(size_t pIndex) -> Row
{
	return mData.data() + getRowSize() * pIndex;
}


template <typename T>
T const& Array2D<T>::getRowPart(
	size_t pIndex,
	size_t pPart) const
{
	return getRow(pIndex)[pPart];
}


template <typename T>
T& Array2D<T>::getRowPart(
	size_t pIndex,
	size_t pPart)
{
	return getRow(pIndex)[pPart];
}


template <typename T>
auto Array2D<T>::operator[](size_t pIndex) const -> RowConst
{
	return getRow(pIndex);
}


template <typename T>
auto Array2D<T>::operator[](size_t pIndex) -> Row
{
	return getRow(pIndex);
}


template <typename T>
auto Array2D<T>::insert(
	Iterator 	pPosition,
	T const& 	pValue) -> Iterator
{
	return mData.insert(pPosition, pValue);
}


template <typename T>
auto Array2D<T>::insert(
	Iterator 	pPosition,
	T&& 		pValue) -> Iterator
{
	return mData.insert(pPosition, std::forward<T>(pValue));
}


template <typename T>
auto Array2D<T>::erase(Iterator pPosition) -> Iterator
{
	return mData.erase(pPosition);
}


template <typename T>
size_t Array2D<T>::size() const
{
	return mData.size();
}


template <typename T>
size_t Array2D<T>::getRowSize() const
{
	return mRowSize;
}


template <typename T>
size_t Array2D<T>::getRowCount() const
{
	return size() / getRowSize();
}


template <typename T>
auto Array2D<T>::begin() const -> IteratorConst
{
	mData.begin();
}


template <typename T>
auto Array2D<T>::begin() -> Iterator
{
	mData.begin();
}


template <typename T>
auto Array2D<T>::end() const -> IteratorConst
{
	mData.end();
}


template <typename T>
auto Array2D<T>::end() -> Iterator
{
	mData.end();
}


template <typename T>
auto Array2D<T>::beginRow(size_t pRowNumber) const -> IteratorConst
{
	return begin() + mRowSize * pRowNumber;
}


template <typename T>
auto Array2D<T>::beginRow(size_t pRowNumber) -> Iterator
{
	return begin() + mRowSize * pRowNumber;
}


template <typename T>
auto Array2D<T>::endRow(size_t pRowNumber) const -> IteratorConst
{
	return begin() + mRowSize * (pRowNumber + 1);
}


template <typename T>
auto Array2D<T>::endRow(size_t pRowNumber) -> Iterator
{
	return begin() + mRowSize * (pRowNumber + 1);
}


	}
}
