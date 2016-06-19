#pragma once

template<int T>
class gray_code
{
public:
	gray_code();
	gray_code(const std::bitset<T>& binary);
	gray_code(unsigned int a);
	gray_code(const std::string& s);
	gray_code(const gray_code<T>& other);
	~gray_code(){};

	void print_gray() const;
	void print_binary() const;

	std::bitset<T> getGray() const;
	std::bitset<T> getBinary() const;

	void operator=(const gray_code<T>& other);

	void increment(unsigned int count = 1);
	void decrement(unsigned int count = 1);
private:
	std::bitset<T> gray_;
	std::bitset<T> binary_;

	void computeGray();
	void computeBinary();
};


template<int T>
gray_code<T>::gray_code() 
{
}

template<int T>
gray_code<T>::gray_code(const gray_code<T>& other) : gray_(other.getGray), binary_(other.getBinary)
{
}

template<int T>
gray_code<T>::gray_code(const std::bitset<T>& binary) : binary_(binary)
{
	computeGray();
}

template<int T>
gray_code<T>::gray_code(unsigned int a) : binary_(a)
{
	computeGray();
}

template<int T>
gray_code<T>::gray_code(const std::string& s) : binary_(s)
{
	computeGray();
}

template<int T>
void gray_code<T>::computeBinary()
{
	for (int i = gray_.size() - 1; i >= 0; i--){
		if (i == gray_.size() - 1){
			binary_[gray_.size() - 1] = gray_[gray_.size() - 1];
		}
		else {
			if (gray_[i] == 0){
				binary_[i] = binary_[i + 1];
			}
			else {
				binary_[i] = !binary_[i + 1];
			}
		}
	}
}

template<int T>
void gray_code<T>::computeGray()
{
	for (int i = binary_.size() - 1; i >= 0; i--){
		if (i == binary_.size() - 1){
			gray_[binary_.size() - 1] = binary_[binary_.size() - 1];
		}
		else {
			gray_[i] = (binary_[i] ^ binary_[i + 1]);
		}
	};
}

template<int T>
std::bitset<T> gray_code<T>::getGray() const
{
	return gray_;
}

template<int T>
std::bitset<T> gray_code<T>::getBinary() const
{
	return binary_;
}

template<int T>
void gray_code<T>::operator=(const gray_code<T>& other)
{
	gray_ = other.gray_;
	binary_ = other.binary_;
}

template<int T>
void gray_code<T>::increment(unsigned int count) {
	binary_ = std::bitset<T>(binary_.to_ulong() + count);
	computeGray();
}

template<int T>
void gray_code<T>::decrement(unsigned int count) {
	binary_ = std::bitset<T>(binary_.to_ulong() - count);
	computeGray();
}

template<int T>
void gray_code<T>::print_gray() const
{
	std::cout << "gray" << std::endl;
	std::cout << gray_;
	std::cout << std::endl;
}


template<int T>
void gray_code<T>::print_binary() const
{
	std::cout << "binary" << std::endl;
	std::cout << binary_;
	std::cout << std::endl;
}
