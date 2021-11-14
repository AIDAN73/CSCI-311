#include <queue>
#include <deque>
#include <iostream>
#include "Airplane.h"
#include "priorityQueue.h"
using namespace std;

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
			//plane->emergency = true;							//set planes with very low fuel to emergency
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
			i--;
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
	emergencyArrivingQueue = updateFuelQueue(emergencyArrivingQueue, "emergencyArrivingQueue");
    updateFuelPriorityQueue();
	arrivingQueue = updateFuelQueue(arrivingQueue, "arrivingQueue");
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

	if (emergencyDepartingQueue.size()!=0)		//departing emergencies first
	{
		emergencyDepartingQueue = process(emergencyDepartingQueue);
		return;
	}
	else if (emergencyArrivingQueue.size()!=0)			//arriving emergencies after
	{
		emergencyArrivingQueue = process(emergencyArrivingQueue);	
		return;
	}
	else if (departingQueue.size() !=0)				//no emergencies, prioritize takeoffs
	{
		departingQueue = process(departingQueue);
		return;
	}
	else if (lowFuelArrivingQueue.pQueue.size()!=0)		//low fuel planes next
	{
		cout<<"\t\t";
		lowFuelArrivingQueue.pop()->displayPlane();
		return;
	}
	else if (arrivingQueue.size()!=0) 
		arrivingQueue = process(arrivingQueue);		//if nothing else, land planes
}


//considers the active queues of planes and picks a plane to land, prioritizing landings
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
	if (planesInSimulation()) return true;
	if (simulationPlanes.size()!=0)
	{
		return (simulationPlanes[0]->entranceTime == t);
	}
	return false;
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
			//cout<<"Runway A"<<endl;
			//displayAllQueues();
			runwayA();
			//cout<<"Runway B"<<endl;
			runwayB(); 
			//cout<<"Updating fuel"<<endl;
			updateFuelAll();
			//cout<<"Finished timestep"<<endl;
		}
		time++;
    }
    
}