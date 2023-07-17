#include <iostream>


template <class T>
class sString {
public:
	sString() : pData(nullptr), iSize(0) {}
	sString(const char* s) : iSize(strlen(s)) {
		pData = new char[iSize + 1];
		strcpy_s(pData, iSize + 1, s);
	}
	~sString() {
		if (pData != nullptr) {
			delete[] pData;
		}
	}
	sString(const sString& sS) : iSize(sS.iSize) {
		pData = new char[iSize + 1];
		strcpy_s(pData, iSize + 1, sS.pData);
	}
	sString(sString&& sS) noexcept : pData(sS.pData), iSize(sS.iSize) {
		sS.pData = nullptr;
	}
	sString& operator=(const sString& sS) {
		if (this != &sS) {
			delete[] pData;
			iSize = sS.iSize;
			pData = new char[iSize + 1];
			strcpy_s(pData, iSize + 1, sS.pData);
		}
		return *this;
	}
	sString& operator=(sString&& sS) noexcept {
		if (this != &sS) {
			pData = sS.pData;
			iSize = sS.iSize;
			sS.pData = nullptr;
		}
		return *this;
	}
	sString operator+(const sString& sS) const {
		sString tmp;
		tmp.iSize = iSize + sS.iSize;
		tmp.pData = new char[tmp.iSize + 1];
		strcpy_s(tmp.pData, iSize + 1, pData);
		strcpy_s(tmp.pData + iSize, tmp.iSize - iSize + 1, sS.pData);
		return tmp;
	}
	sString& operator+=(const sString& sS) {
		sString tmp;
		tmp.iSize = iSize + sS.iSize;
		tmp.pData = new char[tmp.iSize + 1];
		if (pData) {
			strcpy_s(tmp.pData, iSize + 1, sS.pData);
		}
		strcpy_s(tmp.pData + iSize, tmp.iSize - iSize + 1, sS.pData);
		delete pData;
		pData = new char[tmp.iSize + 1];
		strcpy_s(pData, tmp.iSize + 1, tmp.pData);
		return *this;
	}
	bool operator==(const sString& sS) const {
		return (strcmp(this->pData, sS.pData) == 0);
	}

	char* getData() const {
		return pData;
	}
	int size() const {
		return iSize;
	}

private:
	char* pData;
	int iSize;
};

std::ostream& operator<<(std::ostream& os, const sString& sS) {
	os << sS.getData();
	return os;
}


int main() {
	sString s0;
	sString s1("s1");
	sString s2("s2");

	s0 = s1;
	sString s3 = s2;
	sString s33;
	s33 += s3;
	sString s4;
	s4 = s1 + s2;
	sString s5 = sString("move");
	sString s6 = s0;


	std::cout << s0 << " " << s1 << " " << s2 << " " << s3 << " " << s4 << " " << std::endl;
	std::cout << s5;
}