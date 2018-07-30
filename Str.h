//
// Created by Jeffrey on 5/27/2018.
//

#ifndef ADVCPPCOURSE_STR_H
#define ADVCPPCOURSE_STR_H


#include <string.h>
#include <ostream>
#include <functional>

using namespace std;

namespace jsf2184 {

    class Str {
    public:

        Str() : _bufLen(0), _strLen(0), _buf(nullptr) {}

        Str(const char * src) :Str() {
            cout << "Str() constructor with char * input: '" << src << "'" << endl;
            assign(src, strlen(src));
        }

        Str(const Str &src) : Str() {
            operator=(src);
        }

        Str(Str &&src) : Str() {
//            internalMove(std::move(src), "moveConstructor");
            internalMove(forward<Str &&>(src), "moveConstructor");
        }


        Str &operator=(const Str &src) {
            assign(src._buf, src._strLen);
            return *this;
        }

        Str &operator=(Str &&src) {
            return internalMove(std::move(src), "operator=");
        }

        Str & internalMove(Str &&src, const string &label) {
            cout << label
                 <<  " src w/ value: "
                 << src
                 << " will override old value: "
                 << this->_buf
                 << endl;
            char *temp = _buf;
            _buf = src._buf;
            src._buf = temp;
            _bufLen = src._bufLen;
            _strLen = src._strLen;
            return *this;
        }




        Str &assign(const char *src, size_t strLen) {
            bool needAlloc = _buf == nullptr || strLen + 1 > _bufLen;
            if (_buf != nullptr && needAlloc) {
                delete[](_buf);
            }
            allocAndCopy(strLen, src, needAlloc);
        }

        void allocAndCopy(size_t strLen, const char *src, bool needAlloc) {
            if (needAlloc) {
                _bufLen = strLen + 1;
                _buf = new char[_bufLen];
            }
            _strLen = strLen;
            memcpy(_buf, src, strLen+1);
        }

        virtual ~Str() {
            cout << "~Str() with _buf = '" << _buf << "'" << endl;
            if (_buf != nullptr) {
                delete[](_buf);
                _buf = nullptr;
            }
        }

        friend ostream &operator<<(ostream &os, const Str &str) {
            os << str._buf;
        }

        char *getVal() {
            return _buf;
        }

        bool operator==(const Str &other) {
            if (_buf == nullptr && other._buf == nullptr) {
                return true;
            }
            if (_buf != nullptr && other._buf != nullptr) {
                if (_strLen == other._strLen) {
                    return strcmp(_buf, other._buf) == 0;
                }
            }
            return false;
        }

    private:
        char *_buf;
        size_t _bufLen;
        size_t _strLen;
    };

}

#endif //ADVCPPCOURSE_STR_H
