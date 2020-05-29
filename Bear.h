#ifndef BEAR_H
#define BEAR_H

using namespace std;

bool bearAlive = true;

class Bear
{
public:
	
	void eatOfHoney(int &amountOfHoney, mutex &mtx)
	{
		while (bearAlive)
		{
			unique_lock<mutex> ul(mtx);
			//mtx.lock();
			amountOfHoney -= 50;
			checkBearAlive(amountOfHoney);
			//mtx.unlock();
			ul.unlock();
			this_thread::sleep_for(chrono::milliseconds(5000));
		}	
	}
	void checkBearAlive(int &amountOfHoney)
	{
		if (bearHungry & (amountOfHoney < 0)) 
		{ 
			cout << "ÌÅÄÂÅÄÜ ÑÊÎÍ×ÀËÑß! ÍÀÄÎ ÁÛËÎ ËÓ×ØÅ ÊÎÐÌÈÒÜ!" << endl;
			
			bearAlive = false;
			//cout << bearAlive << endl << getBearAlive() << endl;
		}	else
		{
			bearHungry = false;
			if (amountOfHoney >= 0)
			{
				cout << "ID ïîòîêà = " << this_thread::get_id() << "\t ÌÅÄÂÅÄÜ ÑÛÒ! Ìåäà îñòàëîñü = " << amountOfHoney << endl;
			}
			else
			{
				amountOfHoney = 0;
				bearHungry = true;
				cout << "ID ïîòîêà = " << this_thread::get_id() << "\t ÌÅÄÂÅÄÜ ÃÎËÎÄÅÍ! Ñðî÷íî ìåäà!" << endl;
			}
		}
	}
	/*
	bool getBearAlive()
	{
		return bearAlive;	
	}
	*/

private:
	bool bearHungry = false;
	//bool bearAlive = true;
};

#endif //BEAR_H