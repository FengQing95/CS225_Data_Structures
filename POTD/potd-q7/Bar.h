#pragma once
#include <string>
#include "Foo.h"

namespace potd{
    class Bar{
    public:
        Bar(std::string name);
        Bar(const Bar & that);
        ~Bar();
        Bar & operator=(const Bar & that);
        std::string get_name() const;
    private:
        potd::Foo * f_;
    };
}
