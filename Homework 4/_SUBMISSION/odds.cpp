void removeOdds(vector<int>& v)
{
	vector<int>::iterator k;
	for (k = v.begin(); k != v.end(); k++) {
		if (*k % 2 == 1) {
			k = v.erase(k);
			k--;
		}
	}
}