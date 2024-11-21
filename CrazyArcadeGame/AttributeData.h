#pragma once

/*
*	FAttributeData는 기본 타입 멤버 변수들과 달리,
*	public으로 접근함을 알림
*/
template<typename T>
struct FAttributeData
{

};

template<>
struct FAttributeData<float>
{
	typedef float T;

public:
	T GetBaseValue() const
	{
		return this->BaseValue;
	}

	void SetBaseValue(T Value)
	{
		this->BaseValue = Value;
	}

	operator T()
	{
		return this->BaseValue;
	}

	/*
	* 연산자 오버로딩
	*/
	inline bool operator==(const FAttributeData& Other)
	{
		return this->BaseValue == Other.BaseValue;
	}
	inline bool operator==(T Value)
	{
		return this->BaseValue == Value;
	}
	inline FAttributeData operator+(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue += Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator+(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue += Value;
		return NewData;
	}
	inline FAttributeData operator-(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue -= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator-(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue -= Value;
		return NewData;
	}
	inline FAttributeData operator*(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue *= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator*(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue *= Value;
		return NewData;
	}
	inline FAttributeData operator/(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue /= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator/(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue /= Value;
		return NewData;
	}
	inline FAttributeData& operator=(const FAttributeData& Other)
	{
		this->BaseValue = Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator=(T Value)
	{
		this->BaseValue = Value;
		return *this;
	}
	inline FAttributeData& operator+=(const FAttributeData& Other)
	{
		this->BaseValue += Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator+=(T Value)
	{
		this->BaseValue += Value;
		return *this;
	}
	inline FAttributeData& operator-=(const FAttributeData& Other)
	{
		this->BaseValue -= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator-=(T Value)
	{
		this->BaseValue -= Value;
		return *this;
	}
	inline FAttributeData& operator*=(const FAttributeData& Other)
	{
		this->BaseValue *= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator*=(T Value)
	{
		this->BaseValue *= Value;
		return *this;
	}
	inline FAttributeData& operator/=(const FAttributeData& Other)
	{
		this->BaseValue /= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator/=(T Value)
	{
		this->BaseValue /= Value;
		return *this;
	}

protected:
	T BaseValue;
};

template<>
struct FAttributeData<int>
{
	typedef int T;

public:
	T GetBaseValue() const
	{
		return this->BaseValue;
	}

	void SetBaseValue(T Value)
	{
		this->BaseValue = Value;
	}

	operator T()
	{
		return this->BaseValue;
	}

	/*
	* 연산자 오버로딩
	*/
	inline bool operator==(const FAttributeData& Other)
	{
		return this->BaseValue == Other.BaseValue;
	}
	inline bool operator==(T Value)
	{
		return this->BaseValue == Value;
	}
	inline FAttributeData operator+(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue += Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator+(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue += Value;
		return NewData;
	}
	inline FAttributeData operator-(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue -= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator-(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue -= Value;
		return NewData;
	}
	inline FAttributeData operator*(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue *= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator*(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue *= Value;
		return NewData;
	}
	inline FAttributeData operator/(const FAttributeData& Other)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue /= Other.BaseValue;
		return NewData;
	}
	inline FAttributeData operator/(T Value)
	{
		FAttributeData NewData = *this;
		NewData.BaseValue /= Value;
		return NewData;
	}
	inline FAttributeData& operator=(const FAttributeData& Other)
	{
		this->BaseValue = Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator=(T Value)
	{
		this->BaseValue = Value;
		return *this;
	}
	inline FAttributeData& operator+=(const FAttributeData& Other)
	{
		this->BaseValue += Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator+=(T Value)
	{
		this->BaseValue += Value;
		return *this;
	}
	inline FAttributeData& operator-=(const FAttributeData& Other)
	{
		this->BaseValue -= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator-=(T Value)
	{
		this->BaseValue -= Value;
		return *this;
	}
	inline FAttributeData& operator*=(const FAttributeData& Other)
	{
		this->BaseValue *= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator*=(T Value)
	{
		this->BaseValue *= Value;
		return *this;
	}
	inline FAttributeData& operator/=(const FAttributeData& Other)
	{
		this->BaseValue /= Other.BaseValue;
		return *this;
	}
	inline FAttributeData& operator/=(T Value)
	{
		this->BaseValue /= Value;
		return *this;
	}

protected:
	T BaseValue;
};
