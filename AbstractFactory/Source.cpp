#include <iostream>
using namespace std;

class Herbivore abstract {
protected:
	unsigned int weight;
	bool life;
public:
	Herbivore(unsigned int weight) : weight(weight), life(true) {};

	void EatGrass() {
		if (life == false)
			return;
		weight += 10;
	}

	int GetWeigth()const {
		return weight;
	}

	bool IsAlive()const {
		return life;
	}

	void SetLife(bool life) {
		this->life = life;
	}

	virtual string GetName() = 0; 
};


class Wildebeest :public Herbivore {
public:
	Wildebeest() :Herbivore(150) {};
	string GetName() override {
		return "Wildebeest";
	}
};

class Bison : public Herbivore {
public:
	Bison() :Herbivore(500) {};
	string GetName() override {
		return "Bison";
	}
};

class Elk : public Herbivore {
public:
	Elk() :Herbivore(250) {};
	string GetName() override {
		return "Elk";
	}
};


class Carnivore abstract {
protected:
	unsigned int power;
public:
	Carnivore(unsigned int power) {
		this->power = power;
	}
	unsigned int GetPower()const {
		return power;
	}

	void Eat(Herbivore*& herbivore) {
		if (this->power >= herbivore->GetWeigth())
		{
			this->power += 10;
			herbivore->SetLife(false);
			
			cout << this->GetName() << " has eaten " << herbivore->GetName()<<endl;
			
		}
		else
			this->power -= 10;

	};
	virtual string GetName() = 0;
	
};

class Lion : public Carnivore {
public:
	Lion() :Carnivore(500) {};
	string GetName() override {
		return "Lion";
	}
};

class Wolf : public Carnivore {
public:
	Wolf() :Carnivore(240) {};
	string GetName() override {
		return "Wolf";
	}
};

class Tiger: public Carnivore {
public:
	Tiger() :Carnivore(450) {};
	string GetName() override {
		return "Tiger";
	}
};

class Continent abstract { //abstract factory
public:
	
	virtual void GetName() = 0;
	virtual Carnivore* CreateCarnivore() = 0;
	virtual Herbivore* CreateHerbivore() = 0;
};

class Africa :public Continent {
	void GetName()override {
		cout << "Africa" << endl;
	}
	Carnivore* CreateCarnivore() override {
		return new Lion();
	}
	Herbivore* CreateHerbivore() override {
		return new Wildebeest();
	}
};

class America : public Continent {
	void GetName() override {
		cout << "America" << endl;
	}
	Carnivore* CreateCarnivore()override {
		return new Wolf();
	}
	Herbivore* CreateHerbivore()override {
		return new Bison();
	}
};

class Eurasia: public Continent {
	void GetName() override {
		cout << "Eurasia" << endl;
	}
	Carnivore* CreateCarnivore()override {
		return new Tiger();
	}
	Herbivore* CreateHerbivore()override {
		return new Elk();
	}
};

class Client {
private:
	Carnivore* carnivore;
	Herbivore* herbivore;

public:
	Client(Continent* continent) {
		carnivore = continent->CreateCarnivore();
		herbivore = continent->CreateHerbivore();
	}
	void Start() {
		FeedHerbivores();
		HuntHerbivores();
		cout << "Power of "<<carnivore->GetName()<<':'<< carnivore->GetPower()<<endl;
		cout << "Is "<<herbivore->GetName()<<" alive:" <<boolalpha<<herbivore->IsAlive()<<endl<<endl<<endl;
	}

	string GetCarnivoreName() {
		return carnivore->GetName();
	}

	string GetHerbivoreName() {
		return herbivore->GetName();
	}

	void FeedHerbivores() {
		herbivore->EatGrass();
	}

	void HuntHerbivores() {
		carnivore->Eat(herbivore);
	}
};


int main() {
	Continent* continent = new Africa();
	Client* client = new Client(continent);
	client->Start();
	delete continent;
	delete client;

	continent = new Eurasia();
	client = new Client(continent);
	client->Start();
	delete continent;
	delete client;

	continent = new America();
	client = new Client(continent);
	client->Start();
	delete continent;
	delete client;
	

	return 0;
}

