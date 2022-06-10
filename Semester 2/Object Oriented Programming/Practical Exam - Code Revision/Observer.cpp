#include "Observer.h"

void Subject::addObserver(Observer* obs)
{
	this->repo.push_back(obs);
}

void Subject::removeObserver(Observer* obs)
{
	for (int i = 0; i < repo.size(); ++i) {
		if (repo[i] == obs) {
			repo.erase(repo.begin() + i);
			return;
		}
	}
}

void Subject::notify()
{
	for (auto it : repo)
		it->update();
}
