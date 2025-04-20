#ifndef ALL_CLASSES_H
#define ALL_CLASSES_H

#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0; //________________ FAT INTERFACE: INTERFACE SEGREGATION PRICIPLE BROKEN
    virtual std::string printAsText() const = 0; //________________ REASON: PARENT CLASS TRIES TO CONTAIN METHOD REALISATIONS FOR ALL DERIVED CLASSES
    virtual std::string printAsJSON() const = 0;
};

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");//__________LESKOV PRICIPLE BROKEN
        }
        return "<html>" + data_ + "<html/>";            //__________REASON: USE OF DERIVED CLASSES MAY LEAD TO EXCEPTION THROWN
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream &file, const Printable& printable, Data::Format format)
{
    switch (format) //_______________________________________________ OPEN-CLOSED PRINCIPLE BROKEN
    {               //_______________________________________________ REASON: ADDING NEW FORMATS WILL NECESSITATE CHANGING SWITCH-CASE CONSTRUCTION
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}

#endif // ALL_CLASSES_H
