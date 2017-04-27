/*
 * Written by Moskvichev A.V.
 * PUBLIC DOMAIN
 */

#ifndef PATTERNS_OBSERVABLE_H
#define PATTERNS_OBSERVABLE_H

#include <vector>

/**
 * This template defines Observable object pattern.
 */
template<class O> class Observable
{
public:
    typedef O Observer;
    typename std::vector<O*>::iterator OIt;

    Observable()
    {
    }

    void AddObserver(O *_observer)
    {
        for (typename std::vector<O*>::iterator it = observers.begin();
             it < observers.end(); it++) {
            if (*it == _observer)
                return ;
        }
        observers.push_back(_observer);
    }

    void RemoveObserver(O *_observer)
    {
        for (typename std::vector<O*>::iterator it = observers.begin();
             it < observers.end(); it++) {
            if (*it == _observer) {
                observers.erase(it);
                return ;
            }
        }
    }

protected:
    std::vector<O*> observers;
};

#define SAFE_REPLACE_OBSERVER(O, oldO, newO) do {                    \
    if (oldO != NULL) {                                                \
        oldO->RemoveObserver(O);                                    \
    }                                                                \
                                                                    \
    if (newO != NULL) {                                                \
        newO->AddObserver(O);                                        \
    }                                                                \
} while (0)

#define SAFE_REMOVE_OBSERVER(O, oldO) do {                            \
    if (oldO != NULL) {                                                \
        oldO->RemoveObserver(O);                                    \
    }                                                                \
} while (0)

#endif /* PATTERNS_OBSERVABLE_H */
