void listAll(const Domain* d, string path) // two-parameter overload
{
	if (d->subdomains().size() == 0) {
		cout << path << endl;
		return;
	}
	else {
		if (path != "") {
			path = "." + path;
		}
		for (size_t k = 0; k < d->subdomains().size(); k++) {
			listAll(d->subdomains()[k], d->subdomains()[k]->label() + path);
		}
	}
}