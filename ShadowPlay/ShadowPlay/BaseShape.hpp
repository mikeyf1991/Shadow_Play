#ifndef SHAPE_HPP
#define SHAPE_HPP

template <typename T>
class BaseShape
{
public:
	const T& Shape() const
	{
		return m_shape;
	}

	T& Shape()
	{
		return m_shape;
	}
protected:
	T m_shape;
};

#endif