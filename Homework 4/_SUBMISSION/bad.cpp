void removeBad(list<Movie*>& li)
{
	for (list<Movie*>::iterator p = li.begin(); p != li.end(); p++) {
		if ((*p)->rating() < 55) { //modified
			delete *p; //li is a list of pointers to Movie, so removing the pointer will not automatically destroy the object
			p = li.erase(p);
			p--;
		}
	}
}