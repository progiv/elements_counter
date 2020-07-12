#include "counter.h"

#include <iostream>
#include <tinyxml2.h>

namespace {

class Counter: public tinyxml2::XMLVisitor {
public:
    int count() const
    {
        return counter_;
    }

    // Visit an element.
    bool VisitEnter(const tinyxml2::XMLElement& /*element*/,
            const tinyxml2::XMLAttribute* /*firstAttribute*/ ) override
    {
        counter_++;
        return true;
    }

private:
    int counter_ = 0;
};

}

int countElements(const std::string& document)
{
    tinyxml2::XMLDocument doc;

    const auto error = doc.Parse(document.c_str(), document.size());
    if (tinyxml2::XML_SUCCESS!=error) {
        std::cerr << "tinyxml2: Failed to parse document";
        return 0;
    }

    Counter counter;
    doc.Accept(&counter);

    return counter.count();
}
