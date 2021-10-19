#include <queue>
#include <deque>
#include <iostream>
#include "Airplane.h"
using namespace std;

deque<Airplane*> simulationPlanes;						//list of airplane pointers to feed into program

deque<Airplane*> departingQueue;						//normal and emergency planes are FIFO, low fuel are sorted by minimum fuel
deque<Airplane*> emergencyDepartingQueue;				
deque<Airplane*> arrivingQueue;							
deque<Airplane*> lowFuelArrivingQueue;					
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
    displayQueue(lowFuelArrivingQueue);

    cout<<endl<<"Emergency Arriving Queue: "<<endl;
    displayQueue(emergencyArrivingQueue);
    cout<<"*************************************************************************************"<<endl;

}

//used by addPlanes to sort a given plane from the inputted list into the appropriate queue.  
void sortPlane(Airplane* plane)
{
	if (plane->intent == "arriving")
	{
		if (plane->emergency == true || plane->fuel <= 2) emergencyArrivingQueue.push_back(plane);
		else if (plane->fuel <= 20) lowFuelArrivingQueue.push_back(plane);
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
	for (int i; i=workingQueue.size(); i++)
	{
		workingQueue[i]->fuel = workingQueue[i]->fuel - 1;
		if(workingQueue[i]->fuel <= 20 && queueType == "arrivingQueue")						//send to emergency if they're arriving
		{
			lowFuelArrivingQueue.push_back(workingQueue[i]);				//add to back of low fuel queue
			workingQueue.erase(workingQueue.begin() + i);										//delete 
		}
	}
    return workingQueue;
}

/*
void updateFuelPriorityQueue()
{

}
*/

void updateFuelall()
{
	departingQueue = updateFuelQueue(departingQueue, "departingQueue");
	emergencyDepartingQueue = updateFuelQueue(emergencyDepartingQueue, "emergencyDepartingQueue");
	arrivingQueue = updateFuelQueue(arrivingQueue, "arrivingQueue");
    //lowFuelArrivingQueue = updateFuelPriorityQueue(lowFuelArrivingQueue, "lowFuelArrivingQueue");
	emergencyArrivingQueue = updateFuelQueue(emergencyArrivingQueue, "emergencyArrivingQueue");
	
}


/*
void runwayA()
{
	if ((departingQueue !=0) && (emergencyDepartingQueue.size==0) && (emergencyArrivingQueue.size==0))		//people to takeoff, no emergencies 
		takeoff(departingQueue.pop);

	else if (emergencyDepartingQueue.size!=0)		//departing emergencies first
		takeoff(emergencyDepartingQueue.pop);

	else if (emergencyArrivingQueue.size!=0)		//arriving emergencies after
		land(emergencyArrivingQueue.pop);

	else land(arrivingQueue)



}
*/

int main()
{
    Airplane plane0 (1,0,"arriving",false,30);
    Airplane plane1 (3,1,"departing",false,50);
    Airplane plane2 (3,2,"arriving",false,1);
    Airplane plane3 (5,3,"arriving",false,15);
    Airplane plane4 (6,4,"departing",true,50);
    Airplane plane5 (7,5,"arriving",false,30);
    Airplane plane6 (7,6,"departing",false,50);
    

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


    for (int i=0; i<8; i++)
    {
        cout<<endl<<"TIME: "<<i<<endl;
        addPlanes(i);
        displayAllQueues();
    }
    



	/*
	while (there's planes that haven't entered or haven't been serviced)
	{
		addPlanes(timestep)   //adds all the inputted planes that are on that timestep to the holding pattern

		runwayA()				//select a plane to use runway A, prioritizing departures
		runwayB()				//select a plane for runway B, prioritizing arrivals

		updateFuel() 			//suck 1 fuel out of everyone's tanks

		timestep++
	}
	*/
}