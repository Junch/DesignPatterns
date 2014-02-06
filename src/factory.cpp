// http://sourcemaking.com/design_patterns/factory_method/cpp/2

#include <gmock/gmock.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Document {
public:
    Document(std::string fn):name(fn) {}
    virtual void Open() = 0;
    virtual void Close() = 0;
    std::string GetName() {
        return name;
    }

private:
    std::string name;
};

class Application {
public:
    ~Application(){
        for (auto& iter: _docs) {
            iter->Close();
        }
    }

    void NewDocument(std::string name){
        std::cout << "Application: NewDocument()" << '\n';
        auto doc = CreateDocument(name);
        _docs.push_back(doc);
        doc->Open();
    }

    virtual std::shared_ptr<Document> CreateDocument(std::string) = 0;

    void ReportDocs() {
        std::cout << "Application: ReportDocs()" << '\n';
        for (auto& iter: _docs)
            std::cout << "  " << iter->GetName() << '\n';
    }

private:
    std::vector<std::shared_ptr<Document>> _docs;
};

class MyDocument: public Document {
public:
    MyDocument(std::string fn):Document(fn) {}
    void Open() override {
        std::cout << "  MyDocument: Open()" << '\n';
    }

    void Close() override {
        std::cout << "  MyDocument: Close()" << '\n';
    }
};

class MyApplication: public Application {
public:
    std::shared_ptr<Document> CreateDocument(std::string fn) override {
        std::cout << "  MyApplication: CreateDocument()" << '\n';
        return std::make_shared<MyDocument>(fn);
    }
};

TEST(Factory, Demo){
    MyApplication myApp;
    myApp.NewDocument("foo");
    myApp.NewDocument("bar");
    myApp.ReportDocs();
}