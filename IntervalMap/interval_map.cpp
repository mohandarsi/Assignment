#include "Header.h"
#include <assert.h>     /* assert */

template<class K, class V>
class interval_map {
	friend void IntervalMapTest();
	friend void testcaseDuplicate();
	friend void testcaseSize();

private:
	std::map<K, V> m_map;

public:
	// constructor associates whole range of K with val by inserting (K_min, val)
	// into the map
	interval_map(V const& val) {
		m_map.insert(m_map.begin(), std::make_pair(std::numeric_limits<K>::lowest(), val));
	}

	// Assign value val to interval [keyBegin, keyEnd). 
	// Overwrite previous values in this interval. 
	// Do not change values outside this interval.
	// Conforming to the C++ Standard Library conventions, the interval 
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval, 
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {

        //Begin always should  less than end
        if (keyBegin >= keyEnd)
        {
            //throw exception..
            return;
        }

        // create an slot to insert the key
        // while creating the key make sure to maintain previous interval untouched
        // inserting interval like 5,10 with value C, should not affect original interval on/after 10 and before 5

        std::map<K, V>::value_type value1(keyBegin, NULL); // create an slot
        auto resultValue1 = m_map.insert(value1);
        if (resultValue1.second) { // if its inserted then split 
            if (resultValue1.first != m_map.begin()) {
                auto previousValueIter = resultValue1.first;
                resultValue1.first->second = (--previousValueIter)->second;
            }
        }
        
        std::map<K, V>::value_type value2(keyEnd, NULL);
        auto resultValue2 = m_map.insert(value2);

        //if its ovveride the value, it may  divide the already existing intervals.
        // make sure to copy its previous value 
        if (resultValue2.second) {
            if (resultValue2.first != m_map.begin()) {
                auto previousValueIter = resultValue2.first;
                resultValue2.first->second = (--previousValueIter)->second;
            }
        }

		auto end = resultValue2.first;
		
        //assign value
        auto begin = resultValue1.first;
        begin->second = val;
		
		// clear values between begin and end as these are redundent
		while (true) {
			auto iter = begin;
			if (++iter == end) {
				break;
			}
			else {
				m_map.erase(iter);
			}
		}

        //delete duplicates if its present before and after begin.
        //if its present these will be in consequence
        
        auto current = begin;
        auto previous = begin;
        auto next = begin;
        if (begin != m_map.begin()) // compare with previous
        {
            previous--;
            if (previous->second == current->second)
            {
                m_map.erase(current);
                current = previous;
                next = previous;
            }
        }
        next++;
        if (next != m_map.end() )
            if(current->second == next->second) {
               m_map.erase(next);
        }
        
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		return (--m_map.upper_bound(key))->second;
	}
};

////delete duplicates if its present before and after begin.
////if its present these will be in consequence
//auto previous = begin;
//auto next = begin;
//if (begin != m_map.begin()) {
//	--previous;//previous to begin
//	if (previous->second == next->second) {
//		m_map.erase(next);
//		next = previous;
//	}
//	else {
//		previous = next;
//	}
//}
//++next;
//if (next != m_map.end() && previous->second == next->second) {
//	m_map.erase(next);
//}



void testcaseSimple()
{
	interval_map<unsigned int, char> myIntervalMap('A');
	auto c = myIntervalMap[50];
	assert(c == 'A');

	myIntervalMap.assign(10, 15, 'M');
	assert(myIntervalMap[10] == 'M');

	assert(myIntervalMap[14] == 'M');
	assert(myIntervalMap[15] != 'M');

	assert(myIntervalMap[50] == 'A');
}

void testcaseEdgeCases()
{
	interval_map<unsigned int, char> myIntervalMap('A');
	
	myIntervalMap.assign(0, 15, 'M');
	assert(myIntervalMap[0] == 'M');
	assert(myIntervalMap[14] == 'M');

	assert(myIntervalMap[15] != 'M');

	assert(myIntervalMap[50] == 'A');
}

void testcaseSize()
{
	interval_map<unsigned int, char> myIntervalMap('A');

	myIntervalMap.assign(10, 15, 'M');
	myIntervalMap.assign(3, 5, 'M');

	assert(myIntervalMap.m_map.size() == 5);

	assert(myIntervalMap[14] == 'M');
	assert(myIntervalMap[10] == 'M');
	assert(myIntervalMap[3] == 'M');

	assert(myIntervalMap[0] == 'A');
	assert(myIntervalMap[2] == 'A');
	assert(myIntervalMap[50] == 'A');

	

}

void testcaseOverlap()
{
	interval_map<unsigned int, char> myIntervalMap1('A');

	myIntervalMap1.assign(25, 55, 'M');
	myIntervalMap1.assign(4, 15, 'K');

	myIntervalMap1.assign(10, 20, 'P');

	assert(myIntervalMap1[6] == 'K');
	assert(myIntervalMap1[10] == 'P');
	assert(myIntervalMap1[12] == 'P');
	assert(myIntervalMap1[14] == 'P');
	assert(myIntervalMap1[16] == 'P');
	assert(myIntervalMap1[25] == 'M');
}

void testcaseDuplicate()
{

	interval_map<unsigned int, char> myIntervalMap('A');
	myIntervalMap.assign(10, 15, 'M');
	myIntervalMap.assign(15, 20, 'M');

	assert(myIntervalMap.m_map.size() == 3);

	myIntervalMap.assign(5, 10, 'M');
	assert(myIntervalMap.m_map.size() == 3);
	
	myIntervalMap.assign(20, 30, 'M');
	assert(myIntervalMap.m_map.size() == 3);

	myIntervalMap.assign(25, 28, 'M');
	assert(myIntervalMap.m_map.size() == 3);

	myIntervalMap.assign(30, 38, 'M');
	assert(myIntervalMap.m_map.size() == 3);


	interval_map<unsigned int, char> myIntervalMap1('P');

	myIntervalMap1.assign(10, 15, 'M');
	myIntervalMap1.assign(20, 25, 'K');

	myIntervalMap1.assign(15, 24, 'K');

	assert(myIntervalMap1[15] == 'K');
	assert(myIntervalMap1[25] == 'P');


}


// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a function IntervalMapTest() here that tests the
// functionality of the interval_map, for example using a map of unsigned int
// intervals to char.
void IntervalMapTest()
{
	testcaseSimple();
	testcaseEdgeCases();
	testcaseSize();
	testcaseDuplicate();
	testcaseOverlap();

}

//int main()
//{
//	IntervalMapTest();
//}