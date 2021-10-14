#include <queue>
#include <deque>
#include <iostream>
#include "Airplane.h"
using namespace std;

deque<Airplane*> simulationPlanes;						//list of airplane pointers to feed into program

deque<Airplane*> departingQueue;						//(0)normal and emergency planes are FIFO, low fuel are sorted by minimum fuel
deque<Airplane*> emergencyDepartingQueue;				//(1)
deque<Airplane*> arrivingQueue;							//(2)
deque<Airplane*> lowFuelArrivingQueue;					//(3)
deque<Airplane*> emergencyArrivingQueue;				//(4)

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
			sortPlane(simulationPlanes.pop_front());
			planeAdded = true;
		}
	}
}


deque<Airplane*> updateFuelqueue(deque<Airplane*> workingQue, int queueType)
{
	for (int i; i=workingQue.size(); i++)
	{
		workingQue[i]->fuel = workingQue[i]->fuel - 1;
		if(workingQue[i]->fuel <= 20 && queueType == 3)						//send to emergency if they're arriving
			{
				lowFuelArrivingQueue.push_back(workingQue[i]);				//add to back of low fuel queue
				workingQueue.erase(i);										//delete 
			}
		


	}
}

/*
void updateFuelPriorityQueue()
{

}
*/

void updateFuelall()
{
	departingQueue = updateFuelqueue(departingQueue);
	emergencyDepartingQueue = updateFuelqueue(emergencyDepartingQueue);
	arrivingQueue = updateFuelqueue(arrivingQueue);
	emergencyArrivingQueue = updateFuelqueue(emergencyArrivingQueue);
	//lowFuelArrivingQueue = updateFuelPriorityQueue(lowFuelArrivingQueue);
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
	/*
	while (there's planes that haven't entered or haven't been serviced)
	{
		addPlanes(timestep)   //adds all the inputed planes that are on that timestep to the holding pattern

		runwayA()				//select a plane to use runway A, prioritizing departures
		runwayB()				//select a plane for runway B, prioritizing arrivals

		updateFuel() 			//suck 1 fuel out of everyone's tanks

		timestep++
	}
	*/
}