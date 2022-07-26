#pragma once
#include"PJHUtill.h"

class IRefCount
{
private:
	int m_RefNum;
public:
	void Add();
	void Dec();

public:
	IRefCount();
	virtual ~IRefCount() = 0 {};
};

template<class T>
class SPTR
{
public:
	SPTR()						: ptr(nullptr)	{}
	SPTR(std::nullptr_t _ptr)	: ptr(nullptr)		{}
	SPTR(T* _ptr)				: ptr(_ptr)		{ CheckAdd(); }
	SPTR(const SPTR& _ptr)	: ptr(_ptr.ptr) { CheckAdd(); }
	~SPTR() { CheckDec(); }

private:
	T * ptr;

public: //operator function.
	T* operator->() { return ptr; }
	const T* operator->()const { return ptr; }
	SPTR& operator=(T* const _ptr)
	{
		if (_ptr == ptr)
		{
			return *this;
		}

		CheckDec();
		ptr = _ptr;
		CheckAdd();

		return *this;
	}
	SPTR& operator=(const SPTR  _ptr)
	{
		if (_ptr.ptr == ptr)
		{
			return *this;
		}

		CheckDec();
		ptr = _ptr.ptr;
		CheckAdd();

		return *this;
	}

	bool operator==(const std::nullptr_t _ptr) const { return ptr == _ptr; }
	bool operator==(const T* const _ptr) const { return ptr == _ptr; }
	bool operator==(const SPTR& _ptr) const { return ptr == _ptr.ptr; }

	bool operator!=(const std::nullptr_t _ptr) const { return ptr != _ptr; }
	bool operator!=(const T* const _ptr) const { return ptr != _ptr; }
	bool operator!=(const SPTR& _ptr) const { return ptr != _ptr.ptr; }

	template<typename ChangeType>
	operator SPTR<ChangeType>()const
	{
		// ( ChangeType가 부모가 아닌지 확인) && ( T가 부모가 아닌지 확인) .
		if (Compile_Dynamic_Cast<ChangeType, T>::IsRelation() == false && Compile_Dynamic_Cast<T, ChangeType>::IsRelation() == false)
		{
			// 둘다 아니라면 nullptr.
			return nullptr;
		}
		return (ChangeType*)ptr;
	}

	T* Get()
	{
		return ptr;
	}

	template<typename ParentType>
	bool IsParent()const
	{
		return Compile_Dynamic_Cast<ParentType,T>::IsRelation();
	}
	template<typename ParentType>
	bool IsChild()const
	{
		return Compile_Dynamic_Cast<T, ParentType>::IsRelation();
	}

	template<typename ChangeType>
	ChangeType* IsConvert() const
	{
		return dynamic_cast<ChangeType*>(ptr);
	}
private:
	void CheckAdd()
	{
		if (nullptr == ptr)
		{
			return;
		}
		ptr->Add();
	}
	void CheckDec()
	{
		if (nullptr == ptr)
		{
			return;
		}
		ptr->Dec();
	}
};


template<typename T>
bool operator==(std::nullptr_t ptr, const SPTR<T>& sptr) { return sptr.operator==(ptr); }

template<typename T>
bool operator!=(std::nullptr_t ptr, const SPTR<T>& sptr) { return sptr.operator!=(ptr); }