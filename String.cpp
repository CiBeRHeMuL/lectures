#include <iostream>

using namespace std;

class String {
private:
    size_t m_size;
    char *m_str;

public:
    String(): m_size(0), m_str(nullptr) {}

    explicit String(const char *str): String() {
        if (!str) {
            return;
        }

        m_size = strlen(str);

        try {
            m_str = new char[m_size + 1];
            memcpy(m_str, str, m_size);
            m_str[m_size] = '\0';
        } catch (...) {
            m_str = nullptr;
            m_size = 0;
        }
    }

    String(const String &str): String(str.m_str) {}

    ~String() {
        m_size = 0;

        if (m_str) {
            delete [] m_str;
            m_str = nullptr;
        }
    }

    void copy(const char *str, size_t size = 0) {
        if (str == m_str) {
            return;
        }

        if (!str) {
            m_size = 0;
            m_str = nullptr;
            return;
        }

        char *oldStr = m_str;
        size_t oldSize = m_size;

        m_size = size ? size : strlen(str);

        try {
            m_str = new char[m_size + 1];
            memcpy(m_str, str, m_size);
            m_str[m_size] = '\0';
            delete [] oldStr;
        } catch (...) {
            m_str = oldStr;
            m_size = oldSize;
        }
    }

    void copy(const String &str) {
        copy(str.m_str);
    }

    size_t size() const {
        return m_size;
    }

    friend ostream &operator<<(ostream &out, const String &str) {
        if (str.m_str){
            out << str.m_str;
        }
        return out;
    }
};

int main() {
    String a("Hello, World!");
    String b("By, World!");
    String c(a);
    String d;

    cout << a << "\n";
    cout << b << "\n";
    cout << d << "\n";
    cout << c << "\n\n";

    a.copy(b);
    c.copy(c);

    cout << a << "\n";
    cout << b << "\n";
    cout << c << "\n";
    return 0;
}
