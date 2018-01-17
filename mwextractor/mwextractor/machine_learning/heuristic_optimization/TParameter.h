#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>


namespace machine_learning
{
	namespace heuristic_optimization
	{


template<typename T>
class TParameter
{
public:
    TParameter(void)
    {
        this->mName = "";
        this->mMin.clear();
        this->mMax.clear();
        this->mParameter.clear();
        this->mStep.clear();
    }

    TParameter(const std::string& rName,
               const std::vector<T>& rMin,
               const std::vector<T>& rMax,
               const std::vector<T>& rParameter,
               const std::vector<T>& rStep)
    {
        this->mName = rName;
        this->mMin = rMin;
        this->mMax = rMax;
        this->mParameter = rParameter;
        this->mStep = rStep;
    }

    ~TParameter(void) throw()
    {}
    /*
        void setParemeterAt(unsigned int index, int parameter)
        {
            if(index < this->mParameter.size())
            {
                this->mParameter[index] = trimValue(parameter, this->mMin[index], this->mMax[index]);
            }
            else
            {
                throw std::length_error("ERROR: Index out of bound.");
            }
        }
    */

    bool isEqual(const TParameter<T>& rParameter)
    {
        unsigned int size = this->getSize();
        if(rParameter.getSize() != size)
        {
            return false;
        }
        else
        {
            for(unsigned int i=0; i<size; i++)
            {
                if(this->getParameterAt(i) != rParameter.getParameterAt(i))
                {
                    return false;
                }
            }
            return true;
        }
    }

    std::string getName(void)
    {
        return this->mName;
    }

    T getParameterAt(unsigned int index) const
    {
        if(index < this->mParameter.size())
        {
            return mParameter[index];
        }
        else
        {
            throw std::length_error("ERROR: Index out of bound.");
        }
    }

    void setParameterAt(unsigned int index, T value)
    {
        if(index < this->mParameter.size())
        {
            // this->mParameter[index] = value;
            // this->mParameter[index] = this->mStep[index]*((int)(value/this->mStep[index]));
            this->mParameter[index] = trimValue(this->mStep[index]*((int)(value/this->mStep[index])),
                                                this->mMin[index], this->mMax[index]);
        }
        else
        {
            throw std::length_error("ERROR: Index out of bound.");
        }
    }

    unsigned int getSize(void) const
    {
        return this->mParameter.size();
    }

    std::string str(void)
    {
        std::stringstream ret;
        unsigned int size = mParameter.size();
        ret<<this->mName;
        ret<<"[";
        ret<<mParameter[0];
        for(unsigned int i=1; i<size; i++)
        {
            ret<<", ";
            ret<<mParameter[i];
        }
        ret<<"]";
        return ret.str();
    }


protected:
    std::string mName;
    std::vector<T> mMin;
    std::vector<T> mMax;
    std::vector<T> mParameter;
    std::vector<T> mStep;
}; // class TParameter


	}
} // namespace Optimizer

