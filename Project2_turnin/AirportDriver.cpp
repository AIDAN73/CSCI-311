
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <iostream>
using namespace std;


/********************************************************************************************
* Airplane Class                                                                            * 
*********************************************************************************************/
#ifndef AIRPLANE_H
#define AIRPLANE_H

class Airplane
{
    public:
    	int entranceTime;
    	int ID;
    	std::string intent;
    	bool emergency;
    	int fuel;

		//default constructor
    	Airplane()
		{
    		entranceTime = 0;
    		ID = 0;
    		intent = "departing";
    		emergency = false;
    		fuel = 0;
		}

    	//parameterized constructor
		Airplane(int Time, int id, std::string Intent, bool Emergency, int Fuel)
		{
			entranceTime = Time;
    		ID = id;
    		intent = Intent;
    		emergency = Emergency;
    		fuel = Fuel;
		}

		//outputs the info for a plane according to the requirements
    	void displayPlane()
		{
			cout<<boolalpha << entranceTime << " " << ID << " " << intent << " " << emergency << " " << fuel << endl;
		}
};
#endif


/********************************************************************************************
* priorityQueue class                                                                       * 
*********************************************************************************************/
#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

class priorityQueue
{
    private:

		//updates the subheap of the priority queue starting at index i, so that it is a minheap
    	void minHeapify(int i)
		{
			int left = 2 * i + 1;			//set up handy variables
			int right = 2 * i + 2;
			int minI = i;
			int heapSize = pQueue.size()-1;		//tracks the last filled index

			if (left <= heapSize && pQueue[left]->fuel < pQueue[i]->fuel)		//if the left child is smaller, set the min to the left child
			{
					minI = left;
			}
			if (right <= heapSize && pQueue[right]->fuel < pQueue[minI]->fuel)	//if the right child is the smallest, set the min to the right child
			{
				minI = right;
			}
			if (minI != i)
			{
				Airplane* temp = pQueue[i];				//swap the min with the current index, then check the swapped subheap
				pQueue[i] = pQueue[minI];
				pQueue[minI] = temp;
				minHeapify(minI);
			}
		}

    public:

		vector<Airplane*> pQueue;

		//default constructor
    	priorityQueue()
		{}

    	bool empty() { return (pQueue.size() == 0); }

    	int size() { return pQueue.size()-1; }

    	void displayPriorityQueue()
		{
    		for (int i=0; i<pQueue.size(); i++)
			{
				pQueue[i]->displayPlane();
			}
		}

		//pushes a plane into the minheap and sorts it into the correct position based on its fuel
    	void push(Airplane* newPlane)
		{
    		pQueue.push_back(newPlane);				//put it in the last position
    		int i = pQueue.size()-1;
			int parent = (i-1)/2;

    		while(i>0 && pQueue[parent]->fuel > pQueue[i]->fuel)		//check it against its parents, move it up if it's has less fuel
			{
				Airplane* temp = pQueue[i];
				pQueue[i] = pQueue[parent];
				pQueue[parent] = temp;

				i = parent;
			}
		}


		//deletes a plane from the priority queue based on its index. Used to move critically low fuel planes from the middle of the priority queue to the emergency arrivals
    	Airplane* deletePlane(int i)
		{
			Airplane* plane = pQueue[i];
    		pQueue[i] = pQueue[pQueue.size()-1];		//replace index with last value
    		pQueue.pop_back();							//get rid of last value
			int parent = (i-1)/2;

			while (i>0 && pQueue[parent]->fuel > pQueue[i]->fuel)		//sends value up until it belongs
			{
				Airplane* temp = pQueue[i];
				pQueue[i] = pQueue[parent];
				pQueue[parent] = temp;
				i = parent;
			}

    		minHeapify(i);				//re minheapify after all the shuffling
			return plane;
		}

		//deletes and returns the plane with the lowest fuel, while maintaining the minheap
    	Airplane* pop()
		{
    		Airplane* plane = pQueue[0];
    		pQueue[0] = pQueue[pQueue.size()-1];
    		pQueue.pop_back();
    		minHeapify(0);
    		return plane;
		}

		//returns but does not delete the first plane in the minheap
    	Airplane* peek()
		{
    		return pQueue[0];
		}
};

#endif


/********************************************************************************************
* AirportDriver code                                                                        * 
*********************************************************************************************/


deque<Airplane*> simulationPlanes;						//list of airplane pointers to feed into program

deque<Airplane*> departingQueue;						//normal and emergency planes are FIFO, low fuel are sorted by minimum fuel
deque<Airplane*> emergencyDepartingQueue;				
deque<Airplane*> arrivingQueue;								
priorityQueue lowFuelArrivingQueue;						//this holds the low fuel planes as a priority queue. 
deque<Airplane*> emergencyArrivingQueue;				



//displays the airplanes in a specified queue, with the output method specified
void displayQueue(deque<Airplane*> workingQueue)
{
    for (int i=0; i < workingQueue.size(); i++)
    {
        workingQueue[i]->displayPlane();
    }
}

//debugging function used while testing the program. Displays the contents of all the queues of planes. Not used in the end program
void displayAllQueues()
{
    cout<<"*************************************************************************************"<<endl;
    cout<<"Simulation Queue: "<<endl;
    displayQueue(simulationPlanes);

    cout<<endl<<"Departing Queue: "<<endl;
    displayQueue(departingQueue);

    cout<<endl<<"Emergency Departing Queue: "<<endl;
    displayQueue(emergencyDepartingQueue);

    cout<<endl<<"Arriving Queue: "<<endl;
    displayQueue(arrivingQueue);

    cout<<endl<<"Low Fuel Arriving Queue: "<<endl;
    lowFuelArrivingQueue.displayPriorityQueue();

    cout<<endl<<"Emergency Arriving Queue: "<<endl;
    displayQueue(emergencyArrivingQueue);
    cout<<"*************************************************************************************"<<endl;

}


//used by addPlanes to sort a given plane from the inputted list into the appropriate queue.  
void sortPlane(Airplane* plane)
{
	if (plane->intent == "arriving")							//if the plane is coming in. This consideres fuel state
	{
		if (plane->emergency == true || plane->fuel <= 2) 		
		{
			plane->emergency = true;							//set planes with very low fuel to emergency
			emergencyArrivingQueue.push_back(plane);
		}
		else if (plane->fuel <= 20) lowFuelArrivingQueue.push(plane);
		else arrivingQueue.push_back(plane);
	}
	else if (plane->intent == "departing") 						//if the plane is outgoing. Does not consider fuel state
	{
		if (plane->emergency == true) emergencyDepartingQueue.push_back(plane);
		else departingQueue.push_back(plane);
	}
	else cout<<"Unknown intent for plane "<< plane->ID << ": " << plane->intent <<endl;		//in case of typo
}


//checks if there's any planes in the simulationPlanes queue that should be fed into the simulation at given timestep. If there are, it displays them as required, pops
//them from simulationPlanes queue, and puts them into the sort function to sort them into the appropriate queue. 
void addPlanes(int timestep)
{
	cout<<"\tEntering simulation"<<endl;
    if (simulationPlanes.size() == 0) return;				//don't try to add planes if there aren't any left

	bool planeAdded = true;
	while(planeAdded)										//if a plane was added last loop around, check the next one too
	{
		planeAdded = false;
		if(simulationPlanes.front()->entranceTime == timestep)		//if it's the plane's turn
		{
			cout<<"\t\t";
			simulationPlanes.front()->displayPlane();				//display plane, then send it to be sorted and delete it from the simulation queue
			sortPlane(simulationPlanes.front());
            simulationPlanes.pop_front();
			planeAdded = true;
            if (simulationPlanes.size()==0) return;
		}
	}
}

//decreases the fuel of every plane in a queue. If the plane is in the normal arriving queue and hits 20 fuel, it is deleted from the normal queue and sent to the low fuel priority queue
deque<Airplane*> updateFuelQueue(deque<Airplane*> workingQueue, string queueType)
{
	for (int i=0; i<workingQueue.size(); i++)
	{
		workingQueue[i]->fuel = (workingQueue[i]->fuel - 1);
		if(workingQueue[i]->fuel <= 20 && queueType == "arrivingQueue")						//send to low fuel if they're arriving
		{
			lowFuelArrivingQueue.push(workingQueue[i]);										//add to back of low fuel queue
			workingQueue.erase(workingQueue.begin() + i);									//delete 
		}
	}
    return workingQueue;
}

//updates the fuel of all the planes in the low fuel priority queue. If a plane ends up with 2 or less fuel it gets sent to the emergency arriving queue
void updateFuelPriorityQueue()
{
	for (int i=0; i < lowFuelArrivingQueue.pQueue.size(); i++)
	{
		lowFuelArrivingQueue.pQueue[i]->fuel = lowFuelArrivingQueue.pQueue[i]->fuel-1;			//reduce fuel

		if(lowFuelArrivingQueue.pQueue[i]->fuel <= 2)
		{
			emergencyArrivingQueue.push_back(lowFuelArrivingQueue.deletePlane(i));
			i--;
		}
	}
}

//calls the update fuel functions on all the arriving queues
void updateFuelAll()
{
	arrivingQueue = updateFuelQueue(arrivingQueue, "arrivingQueue");
	emergencyArrivingQueue = updateFuelQueue(emergencyArrivingQueue, "emergencyArrivingQueue");
    updateFuelPriorityQueue();
}

//used by the runway functions to process a plane from a given normal queue
deque<Airplane*> process(deque<Airplane*> workingQueue)
{
	cout<<"\t\t";
	workingQueue[0]->displayPlane();
	workingQueue.pop_front();
    return workingQueue;
}


//considers the active queues of planes and picks a plane to land, prioritizing takeoffs
void runwayA()
{
	cout<<"\tRunway A"<<endl;
	if (emergencyArrivingQueue.size()!=0)			//arriving emergencies first
	{
		emergencyArrivingQueue = process(emergencyArrivingQueue);	
		return;
	}
	else if (emergencyDepartingQueue.size()!=0)		//departing emergencies after
	{
		emergencyDepartingQueue = process(emergencyDepartingQueue);
		return;
	}
	else if (lowFuelArrivingQueue.pQueue.size()!=0)		//low fuel planes next
	{
		cout<<"\t\t";
		lowFuelArrivingQueue.pop()->displayPlane();
		return;
	}
	else if (departingQueue.size() !=0)				//no emergencies, prioritize takeoffs
	{
		departingQueue = process(departingQueue);
		return;
	}
	else if (arrivingQueue.size()!=0) 
		arrivingQueue = process(arrivingQueue);		//if nothing else, land planes
}


//considers the active queues of planes and picks a plane to land, prioritizing takeoffs
void runwayB()
{
	cout<<"\tRunway B"<<endl;
	if (emergencyArrivingQueue.size()!=0)			//arriving emergencies first
	{
		emergencyArrivingQueue = process(emergencyArrivingQueue);	
		return;
	}
	else if (emergencyDepartingQueue.size()!=0)		//departing emergencies after
	{
		emergencyDepartingQueue = process(emergencyDepartingQueue);
		return;
	}
	else if (lowFuelArrivingQueue.pQueue.size()!=0)		//low fuel planes next
	{
		cout<<"\t\t";
		lowFuelArrivingQueue.pop()->displayPlane();
		return;
	}
	else if (arrivingQueue.size() !=0)				//no emergencies, prioritize landings
	{
		arrivingQueue = process(arrivingQueue);
		return;
	}
	else if (departingQueue.size()!=0) 
		departingQueue = process(departingQueue);		//if nothing else, takeoff planes
}

//checks if any of the active queues have planes in them 
bool planesInSimulation()
{
	return (emergencyArrivingQueue.size()!=0 || emergencyDepartingQueue.size()!=0 || !lowFuelArrivingQueue.empty() || arrivingQueue.size() !=0 || (departingQueue.size()!=0));
}

//checks if any of the active queues or the simulation queue have planes in them. Used to check if the program should stop
bool planesLeft()
{
	return (simulationPlanes.size()!=0 || planesInSimulation());
}

//checks if any of the active queues planes in them, or if a plane is about to be added at the given time. Used to check if the program should output anything for the given timestep
bool somethingsGonnaHappen(int t)
{
	return ((simulationPlanes[0]->entranceTime == t) || planesInSimulation());
}

//used to convert a string cin input into the expected boolean for the airplane constructor
bool stringToBool( string const& s)
{
	return (s == "true");
}



int main()
{
	int numberOfPlanes = 0;			//how many planes to add to the simulation queue
	cin >> numberOfPlanes;	

	string t, id, intent, emergency, fuel;		//takes them all as strings then turns them into the correct data type

	for (int i=1; i<=numberOfPlanes; i++)		//adds planes to the simulation queue
	{
		cin >> t >> id >> intent >> emergency >> fuel; 

		Airplane* plane = new Airplane(stoi(t), stoi(id), intent, stringToBool(emergency), stoi(fuel));
		simulationPlanes.push_back(plane); 
	}

	int time=0;
    while(planesLeft())							//while there's still planes to service
    {
		if (somethingsGonnaHappen(time))		//don't output anything if nothing's gonna happen on this time step
		{
			cout<<"Time step "<<time<<endl;
        	addPlanes(time);
			runwayA();
			runwayB(); 
			updateFuelAll();
		}
		time++;
    }
}