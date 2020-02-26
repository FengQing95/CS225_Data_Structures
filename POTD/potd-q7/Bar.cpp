#include "Bar.h"
#include "Foo.h"
#include <string>
using namespace potd;

Bar::Bar(std::string name){
    this->f_ = new Foo(name);
}

Bar::Bar(const Bar & that){
    this->f_ = new Foo(that.get_name());
}

Bar::~Bar(){
    delete f_;
}

Bar & Bar::operator=(const Bar & that){
    this->f_->~Foo();
    Foo * f_new = new Foo(that.f_->get_name());
    this->f_ = f_new;
    return * this;
}

std::string Bar::get_name() const{
    return f_->get_name();
}
