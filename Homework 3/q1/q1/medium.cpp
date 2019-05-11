#include <iostream>
#include <string>
using namespace std;

enum CallType { VOICE, TEXT };

class Medium {
//base class
public:
	Medium(string id)
		: m_id(id) {}

	//important: virtual destructor!
	virtual ~Medium() {};

	virtual string connect() const = 0; //medium alone have nothing to specify connect

	virtual string transmit(string msg) const {
		//let's meke this default a text output
		string message = "text: " + msg;
		return message;
	}

	string id() const {
		return m_id;
	}
private:
	string m_id; //this is the only data member right?
};

class TwitterAccount : public Medium {
public:
	TwitterAccount(string id) //twitter only use text
		: Medium(id), m_connect("Tweet") {}

	~TwitterAccount() {
		cout << "Destroying the Twitter account " << id() << "." << endl;
	}

	virtual string connect() const {
		return m_connect;
	}
private:
	string m_connect;

};

class Phone : public Medium{
public:
	Phone(string id, CallType type) //phone might use text or voice
		: Medium(id), m_connect("Call"), m_type(type) {}

	~Phone() {
		cout << "Destroying the phone " << id() << "." << endl;
	}

	virtual string connect() const{
		return m_connect;
	}

	virtual string transmit(string msg) const {
		string message;
		if (m_type == TEXT)
			message = "text: " + msg;
		else
			message = "voice: " + msg;
		
		
		return message;
	}
private:
	string m_connect;
	CallType m_type;
};

class EmailAccount : public Medium {
public:
	EmailAccount(string id) //email will only use text
		: Medium(id), m_connect("Email") {}

	~EmailAccount() {
		cout << "Destroying the email account " << id() << endl;
	}

	virtual string connect() const {
		return m_connect;
	}
private:
	string m_connect;
};

void send(const Medium* m, string msg) {
	cout << m->connect() << " using id " << m->id()
 		<< ", sending " << m->transmit(msg) << endl;
}

int main() {
	Medium* media[4];
	media[0] = new TwitterAccount("UCLABruinAlert");
	// Phone users may prefer messages to be left as voice or text.
	media[1] = new Phone("(310) 825 3894", VOICE);
	media[2] = new Phone("(213) 389 9060", TEXT);
	media[3] = new EmailAccount("jbroon@ucla.edu");

	cout << "Send the message." << endl;
	for (int k = 0; k < 4; k++)
		send(media[k], "Major power outage in West L.A."); 

	// Clean up the media before exiting 
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete media[k];
}