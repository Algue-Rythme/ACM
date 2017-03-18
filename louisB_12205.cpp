#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const unsigned int INFTY = 1000*1000*1000;

enum TypeEvent {
    Police, Phone
};

enum IntervalleType {
    Begining, End
};

struct Event {
    Event(TypeEvent _type, unsigned int _date, unsigned int _id, IntervalleType _intervalle)
    : type(_type), date(_date), id(_id), intervalle(_intervalle) {}
    TypeEvent type;
    unsigned int date;
    unsigned int id;
    IntervalleType intervalle;
    bool operator<(const Event& e) const {
        if (date != e.date)
            return date < e.date;
        return (intervalle == End && e.intervalle == Begining);
    }
};

int main() {
    unsigned int nbPhonesCalls, nbTests;
    while (scanf("%u%u", &nbPhonesCalls, &nbTests)) {
        if (nbPhonesCalls == 0 && nbTests == 0)
            break ;
        vector<Event> events; events.reserve(nbPhonesCalls*2+nbTests*2);
        for (unsigned int call = 0; call < nbPhonesCalls; ++call) {
            unsigned int a, b, start, duration;
            scanf("%u%u%u%u", &a, &b, &start, &duration);
            events.push_back(Event(Phone, start, INFTY, Begining));
            events.push_back(Event(Phone, start+duration, INFTY, End));
        }
        for (unsigned int police = 0; police < nbTests; ++police) {
            unsigned int start, duration;
            scanf("%u%u", &start, &duration);
            events.push_back(Event(Police, start, police, Begining));
            events.push_back(Event(Police, start+duration, police, End));
        }

        vector<unsigned int> policeRange(nbTests, nbPhonesCalls);

        sort(begin(events), end(events));
        unsigned int nbClose = 0;
        for (const Event& e : events) {
            if (e.type == Phone && e.intervalle == End)
                nbClose += 1;
            if (e.type == Police && e.intervalle == Begining)
                policeRange[e.id] -= nbClose;
        }

        unsigned int nbOpen = 0;
        for (unsigned int id = events.size(); id >= 1; --id) {
            Event e = events[id-1];
            if (e.type == Phone && e.intervalle == Begining)
                nbOpen += 1;
            if (e.type == Police && e.intervalle == End)
                policeRange[e.id] -= nbOpen;
        }

        for (unsigned int police : policeRange) {
            printf("%u\n", police);
        }
    }
}
