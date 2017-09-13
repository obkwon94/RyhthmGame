#pragma once

template <class T>
class Array2D
{
private:
	T* _Array2D;
	int _w;
	int _h;
public:
	Array2D(int w, int h)
	{
		_Array2D = new T[w * h];
		_w = w;
		_h = h;
	}
	~Array2D()
	{
		if (NULL != _Array2D)
			delete[] _Array2D;
		_Array2D = NULL;
		_w = 0;
		_h = 0;
	}
	T& operator[] (int index);
	operator T*();

	void Resize(int w, int h);

	bool SaveData(const char* filename);
	bool LoadData(const char* filename);

	int getSize();

	T& GetArray(int x, int y);
};

template <class T>
T& Array2D<T>::operator[] (int index)
{
	return _Array2D[index];
}

template <class T>
Array2D<T>::operator T*()
{
	return _Array2D;
}

template <class T>
void Array2D<T>::Resize(int nw, int nh)
{
	T* newArray2D = new T[nw * nh];
	if (NULL == newArray2D)
		return;

	int minw = _w;
	if (nw < _w)
		minw = nw;
	
	int minh = _h;
	if (_h < nh)
		minh = nh;
	
	for (int y = 0; y < minh; y++)
		for (int x = 0; x < minw; x++)
			newArray2D[(y * nw) + x] = _Array2D[(y * _w) + x];

	if (NULL != _Array2D)
	{
		delete[] _Array2D;
	}
	_Array2D = newArray2D;
	_w = nw;
}

template <class T>
bool Array2D<T>::SaveData(const char* filename)
{
	FILE* fp = fopen(filename, "wb");

	if (NULL == fp)
	{
		printf("can't save");
		return false;
	}
	int ws = fwrite(_Array2D, sizeof(T), getSize(), fp);

	fclose(fp);

	if (ws != getSize())
		return false;

	return true;
}

template <class T>
bool Array2D<T>::LoadData(const char* filename)
{
	FILE* fp = fopen(filename, "rb");

	if (NULL == fp)
	{
		printf("can't load");
		return false;
	}
	int rs = fread(_Array2D, sizeof(T), getSize(), fp);

	fclose(fp);

	if (rs != getSize())
		return false;

	return true;
}

template <class T>
int Array2D<T>::getSize()
{
	return _w * _h;
}
template <class T>
T& Array2D<T>::GetArray(int x, int y)
{
	return _Array2D[(y * _w) + x];
}