#include<iostream>
#include<set>
#include<string>
#include<map>
using namespace std;

class compare_persons {
public:
	bool operator()(pair<string,int> p1, pair<string,int> p2) {
		return p1.second < p2.second;
	}

};


int main() {

	int no_of_transactions, no_of_friends;
	cin>>no_of_transactions>>no_of_friends;

	string x, y;
	int amount;

	map<string,int> net_amt;

	while(no_of_transactions--) {

		cin>>x>>y>>amount;
		if(net_amt.count(x) == 0) {
			net_amt[x] = 0;
		}
		if(net_amt.count(y) == 0) {
			net_amt[y] = 0;
		}
		net_amt[x] -= amount;
		net_amt[y] += amount;
	}

	multiset<pair<string,int>,compare_persons> m;

	for(auto p: net_amt) {

		string person = p.first;
		int amount = p.second;

		if(net_amt[person] != 0) {
			m.insert({person,amount});
		}
	}

	int count = 0;

	while(!m.empty()) {

		auto low = m.begin();
		auto high = prev(m.end());

		string person_debit = low->first;
		int debit = low->second;

		string person_credit = high->first;
		int credit = high->second;

		int settle = min(abs(debit),credit);
		debit += settle;
		credit -= settle;

		m.erase(low);
		m.erase(high);

		cout<<person_debit<<" will pay "<<settle<<" to "<<person_credit<<endl;

		if(debit != 0) {
			m.insert({person_debit,debit});
		}
		if(credit != 0) {
			m.insert({person_credit,credit});
		}
		count++;

	}
	cout<<count;


	return 0;
}
