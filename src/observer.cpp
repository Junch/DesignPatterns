#include <gmock/gmock.h>
#include <string>
#include <list>

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(Subject* theChangedSubject) = 0;
};


class Subject {
public:
    virtual ~Subject() = default;

    virtual void Attach(Observer* o){
        _observers.push_back(o);
    }

    virtual void Detach(Observer* o){
        auto iter = std::find(_observers.begin(), _observers.end(), o);
        if (iter != _observers.end())
            _observers.erase(iter);
    }

    virtual void Notify() {
        for (auto o: _observers)
            o->Update(this);
    }

protected:
    Subject() = default;
private:
    std::list<Observer*> _observers;
};


class NewspaperOffice: public Subject {
public:
    void SendNewsPapper(std::string paper) {
        _paper = paper;
        Notify();
    }

    std::string getPaper() {
        return _paper;
    }

private:
    std::string _paper;
};


class Customer: public Observer {
public:
    void Update(Subject* theChangedSubject) {
        NewspaperOffice* pOffice = static_cast<NewspaperOffice*>(theChangedSubject);
        _paper = pOffice->getPaper();
    }

    std::string getPaper() {
        return _paper;
    }

private:
    std::string _paper;
};


TEST(Observer, NotifyObservers){
    Customer tom, peter;
    NewspaperOffice office;
    office.Attach(&tom);
    office.Attach(&peter);
    office.SendNewsPapper("Paper: Washington Post");
    ASSERT_THAT(tom.getPaper(), testing::Eq("Paper: Washington Post"));
    ASSERT_THAT(peter.getPaper(), testing::Eq("Paper: Washington Post"));
}

TEST(Observer, DetachObserver){
    Customer tom, peter;
    NewspaperOffice office;
    office.Attach(&tom);
    office.Attach(&peter);
    office.Detach(&tom);
    office.SendNewsPapper("Paper: Washington Post");
    ASSERT_THAT(tom.getPaper(), testing::Eq(""));
    ASSERT_THAT(peter.getPaper(), testing::Eq("Paper: Washington Post"));
}
