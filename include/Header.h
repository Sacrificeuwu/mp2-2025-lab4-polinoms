#pragma once
struct Monom {
	double coefficient;
	int degrees;
	Monom* next;
public:
	Monom() :coefficient(0), degrees(0) { next = nullptr; }
	Monom(const double _coefficient, const int _degrees) {
		if (_degrees > 999) throw std::string("degrees cant be more than 999");
		if (_degrees < 0) throw std::string("Degrees cannot be negative");
		if (std::isnan(_coefficient) || std::isinf(_coefficient)) throw std::string("Degrees cannot be null or inf");
		coefficient = _coefficient;
		degrees = _degrees;
	}
};
class Polinom {
	Monom* head;
	int count;
public:
	Polinom() : head(nullptr), count(0) {}
	Polinom(const Monom& m) {
		head = new Monom(m.coefficient, m.degrees);
		count = 1;
	}
	~Polinom() {
		while (head != nullptr) {
			Monom* temp = head;
			head = head->next;
			delete temp;
		}
	}
	bool NotEmpty() {
		Monom* current = head;
		return current != nullptr ? true : false;
	}
    void ptr_add_new_monom(Monom* m) {
        if (m == nullptr) throw std::string("Cannot add null monom pointer");
        if (head == nullptr) {
            head = m;
            head->next = nullptr;
            count = 1;
            return;
        }

        if (m->degrees > head->degrees) {
            m->next = head;
            head = m;
            count++;
            return;
        }

        if (m->degrees == head->degrees) {
            head->coefficient = head->coefficient + m->coefficient;
            delete m;
            if (std::abs(head->coefficient) < 1e-10) {
                Monom* temp = head;
                head = head->next;
                delete temp;
                count--;
            }
            return;
        }

        Monom* current = head;
        while (current->next != nullptr && current->next->degrees > m->degrees) {
            current = current->next;
        }

        if (current->next != nullptr && current->next->degrees == m->degrees) {
            current->next->coefficient += m->coefficient;
            delete m;
            if (std::abs(current->next->coefficient) < 1e-10) {
                Monom* temp = current->next;
                current->next = current->next->next;
                delete temp;
                count--;
            }
        }
        else {
            m->next = current->next;
            current->next = m;
            count++;
        }
    }
    void add_new_monom(const Monom& m) {
        if (head == nullptr) {
            head = new Monom(m.coefficient, m.degrees);
            head->next = nullptr;
            count = 1;
            return;
        }

        if (m.degrees > head->degrees) {
            Monom* newMonom = new Monom(m.coefficient, m.degrees);
            newMonom->next = head;
            head = newMonom;
            count++;
            return;
        }

        if (m.degrees == head->degrees) {
            head->coefficient += m.coefficient;
            if (std::abs(head->coefficient) < 1e-10) {
                Monom* temp = head;
                head = head->next;
                delete temp;
            }
            return;
        }
        Monom* current = head;
        while (current->next != nullptr && current->next->degrees > m.degrees) {
            current = current->next;
        }
        if (current->next != nullptr && current->next->degrees == m.degrees) {
            current->next->coefficient += m.coefficient;
            if (std::abs(current->next->coefficient) < 1e-10) {
                Monom* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
        }
        else {
            Monom* newMonom = new Monom(m.coefficient, m.degrees);
            newMonom->next = current->next;
            current->next = newMonom;
            count++;
        }
    }
    void print() {
        if (head == nullptr) {
            std::cout << "Polynom is empty" << std::endl;
            return;
        }
        Monom* current = head;
        while (current != nullptr) {

            std::cout << current->coefficient
                << "x^" << current->degrees / 100 << " "
                << "y^" << (current->degrees / 10) % 10 << " "
                << "z^" << current->degrees % 10;

            current = current->next;
            if (current != nullptr) {
                std::cout << " + ";
            }
        }
        std::cout << std::endl;
    }
    Polinom(const Polinom& other) : head(nullptr), count(0) {
        if (other.head) {
            Monom* currentOther = other.head;
            Monom* last = nullptr;

            while (currentOther) {
                Monom* newNode = new Monom(currentOther->coefficient, currentOther->degrees);
                newNode->next = nullptr;

                if (!head) {
                    head = newNode;
                }
                else {
                    last->next = newNode;
                }
                last = newNode;

                currentOther = currentOther->next;
                count++;
            }
        }
    }

    Polinom& operator=(const Polinom& other) {
        if (this != &other) { 
            while (head) {
                Monom* temp = head;
                head = head->next;
                delete temp;
            }
            count = 0;

            if (other.head) {
                Monom* currentOther = other.head;
                Monom* last = nullptr;

                while (currentOther) {
                    Monom* newNode = new Monom(currentOther->coefficient, currentOther->degrees);
                    newNode->next = nullptr;

                    if (!head) {
                        head = newNode;
                    }
                    else {
                        last->next = newNode;
                    }
                    last = newNode;

                    currentOther = currentOther->next;
                    count++;
                }
            }
        }
        return *this;
    }
    Polinom operator + (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot add empty polynomials");
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = pol.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->degrees > current2->degrees) {
                Monom* to_add = new Monom(current1->coefficient, current1->degrees);
                ans.ptr_add_new_monom(to_add);
                current1 = current1->next;
            }
            else if (current1->degrees < current2->degrees) {
                Monom* to_add = new Monom(current2->coefficient, current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            else {
                if (std::abs(current1->coefficient + current2->coefficient) >= 1e-10) {
                    Monom* to_add = new Monom(current1->coefficient + current2->coefficient, current1->degrees);
                    ans.ptr_add_new_monom(to_add);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        while (current1 != nullptr) {
            Monom* to_add = new Monom(current1->coefficient, current1->degrees);
            ans.ptr_add_new_monom(to_add);
            current1 = current1->next;
        }
        while (current2 != nullptr) {
            Monom* to_add = new Monom(current2->coefficient, current2->degrees);
            ans.ptr_add_new_monom(to_add);
            current2 = current2->next;
        }

        return ans;
    }
    Polinom  operator - (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot minus empty polynomials");
        Polinom polRevers;
        Monom* current = pol.head;
        while (current != nullptr) {
            Monom* to_add = new Monom(-1 * current->coefficient, current->degrees);
            polRevers.ptr_add_new_monom(to_add);
            current = current->next;
        }
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = polRevers.head;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->degrees > current2->degrees) {
                Monom* to_add = new Monom(current1->coefficient, current1->degrees);
                ans.ptr_add_new_monom(to_add);
                current1 = current1->next;
            }
            else if (current1->degrees < current2->degrees) {
                Monom* to_add = new Monom(current2->coefficient, current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            else {
                if (std::abs(current1->coefficient + current2->coefficient) >= 1e-10) {
                    Monom* to_add = new Monom(current1->coefficient + current2->coefficient, current1->degrees);
                    ans.ptr_add_new_monom(to_add);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }
        while (current1 != nullptr) {
            Monom* to_add = new Monom(current1->coefficient, current1->degrees);
            ans.ptr_add_new_monom(to_add);
            current1 = current1->next;
        }
        while (current2 != nullptr) {
            Monom* to_add = new Monom(current2->coefficient, current2->degrees);
            ans.ptr_add_new_monom(to_add);
            current2 = current2->next;
        }

        return ans;
    }
    Polinom operator * (const Polinom& pol) {
        if (this->head == nullptr || pol.head == nullptr)
            throw std::string("Cannot multiply empty polynomials");
        Polinom ans;
        Monom* current1 = head;
        Monom* current2 = pol.head;
        while (current1 != nullptr) {
            while (current2 != nullptr) {
                Polinom dop;
                if (current1->degrees + current2->degrees > 999) {
                    throw std::string("degrees more than 10 (");
                }
                Monom* to_add = new Monom(current1->coefficient * current2->coefficient, current1->degrees + current2->degrees);
                ans.ptr_add_new_monom(to_add);
                current2 = current2->next;
            }
            current1 = current1->next;
            current2 = pol.head;
        }
        return ans;
    }

};