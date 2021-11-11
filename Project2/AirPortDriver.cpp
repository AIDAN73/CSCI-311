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
priorityQueue lowFuelArrivingQueue;					
deque<Airplane*> emergencyArrivingQueue;				

void displayQueue(deque<Airplane*> workingQueue)
{
    for (int i=0; i < workingQueue.size(); i++)
    {
        workingQueue[i]->displayPlane();
    }
}



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
	if (plane->intent == "arriving")
	{
		if (plane->emergency == true || plane->fuel <= 2) 
		{
			plane->emergency = true;							//set planes with low fuel to emergency
			emergencyArrivingQueue.push_back(plane);
		}
		else if (plane->fuel <= 20) lowFuelArrivingQueue.push(plane);
		else arrivingQueue.push_back(plane);
	}
	else if (plane->intent == "departing") 
	{
		if (plane->emergency == true) emergencyDepartingQueue.push_back(plane);
		else departingQueue.push_back(plane);
	}
	else cout<<"Unknown intent for plane "<< plane->ID << ": " << plane->intent <<endl;
}

//checks if there's any planes in the inputted array that should be fed into the simulation at this timestep. If there are, it pops
//them from simulationPlanes and puts them into the sort function to sort them into the appropriate queue
void addPlanes(int timestep)
{
    if (simulationPlanes.size() == 0) return;

	bool planeAdded = true;
	while(planeAdded)
	{
		planeAdded = false;
		if(simulationPlanes.front()->entranceTime == timestep)
		{
			sortPlane(simulationPlanes.front());
            simulationPlanes.pop_front();
			planeAdded = true;
            if (simulationPlanes.size()==0) return;
		}
	}
}

//decreases the fuel of every plane in a FIFO queue. If the plane is in the normal arriving queue and hits 20 fuel, it is deleted from the normal queue and sent to the low fuel heap
deque<Airplane*> updateFuelQueue(deque<Airplane*> workingQueue, string queueType)
{
	for (int i=0; i<workingQueue.size(); i++)
	{
		workingQueue[i]->fuel = (workingQueue[i]->fuel - 1);
		if(workingQueue[i]->fuel <= 20 && queueType == "arrivingQueue")						//send to emergency if they're arriving
		{
			lowFuelArrivingQueue.push(workingQueue[i]);				//add to back of low fuel queue
			workingQueue.erase(workingQueue.begin() + i);										//delete 
		}
	}
    return workingQueue;
}


void updateFuelPriorityQueue()
{
	for (int i=0; i < lowFuelArrivingQueue.pQueue.size(); i++)
	{
		lowFuelArrivingQueue.pQueue[i]->fuel = lowFuelArrivingQueue.pQueue[i]->fuel-1;			//reduce fuel

		if(lowFuelArrivingQueue.pQueue[i]->fuel <= 2)
		{
			emergencyArrivingQueue.push_back(lowFuelArrivingQueue.deletePlane(i));
		}
	}
}


void updateFuelAll()
{
	departingQueue = updateFuelQueue(departingQueue, "departingQueue");
	emergencyDepartingQueue = updateFuelQueue(emergencyDepartingQueue, "emergencyDepartingQueue");
	arrivingQueue = updateFuelQueue(arrivingQueue, "arrivingQueue");
    updateFuelPriorityQueue();
	emergencyArrivingQueue = updateFuelQueue(emergencyArrivingQueue, "emergencyArrivingQueue");
	
}

//used by the runway functions to process a plane from a given queue
deque<Airplane*> process(deque<Airplane*> workingQueue)
{
	cout<<"\t";
	workingQueue[0]->displayPlane();
	workingQueue.pop_front();
    return workingQueue;
}

void runwayA()
{
	cout<<"Runway A"<<endl;
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
		cout<<"\t";
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


void runwayB()
{
	cout<<"Runway B"<<endl;
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
		cout<<"\t";
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


bool planesLeft()
{
	if (simulationPlanes.size()!=0 || emergencyArrivingQueue.size()!=0 || emergencyDepartingQueue.size()!=0 || lowFuelArrivingQueue.pQueue.size()!=0 || arrivingQueue.size() !=0 || (departingQueue.size()!=0))
	{
		return true;
	}
	return false;
}




int main()
{
	/*
    Airplane plane0 (1,0,"arriving",false,30);
    Airplane plane1 (3,1,"departing",false,50);
    Airplane plane2 (3,2,"arriving",false,1);
    Airplane plane3 (5,3,"arriving",false,15);
    Airplane plane4 (6,4,"departing",true,50);
    Airplane plane5 (7,5,"arriving",false,30);
    Airplane plane6 (7,6,"departing",false,50);*/
    
    Airplane plane0 (1,0,"arriving",false,13);
    Airplane plane1 (1,1,"arriving",false,5);
    Airplane plane2 (1,2,"arriving",false,3);
    Airplane plane3 (1,3,"arriving",false,19);
    Airplane plane4 (1,4,"arriving",false,20);
    Airplane plane5 (1,5,"arriving",false,9);
    Airplane plane6 (1,6,"arriving",false,11);	
	
	Airplane* plane = &plane0;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
    plane = &plane1;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
    plane = &plane2;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
    plane = &plane3;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
    plane = &plane4;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
    plane = &plane5;
    lowFuelArrivingQueue.push(plane);
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
	lowFuelArrivingQueue.pop();
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
	lowFuelArrivingQueue.pop();
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
	lowFuelArrivingQueue.pop();
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
	lowFuelArrivingQueue.pop();
	lowFuelArrivingQueue.displayPriorityQueue();
	cout<<endl;
	lowFuelArrivingQueue.pop();
	lowFuelArrivingQueue.displayPriorityQueue();


/*
    Airplane* plane = &plane0;
    simulationPlanes.push_back(plane);
    plane = &plane1;
    simulationPlanes.push_back(plane);
    plane = &plane2;
    simulationPlanes.push_back(plane);
    plane = &plane3;
    simulationPlanes.push_back(plane);
    plane = &plane4;
    simulationPlanes.push_back(plane);
    plane = &plane5;
    simulationPlanes.push_back(plane);

	int time=0;
    while(planesLeft())
    {
        cout<<endl<<"TIME: "<<time<<endl;
		//cout<<"Adding planes:"<<endl;
        addPlanes(time);
        displayAllQueues();
		//cout<<"Servicing planes:"<<endl;
		runwayA();
		runwayB();
		//cout<<"Updating fuel:"<<endl; 
		updateFuelAll();
		time++;

    }
    */
}