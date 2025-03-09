#pragma once

template<typename ResultType>
class IResolvable{
public:
	virtual ResultType resolve() = 0;
};